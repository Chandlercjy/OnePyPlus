#include "../../Constants.h"
#include "../models/GeneralOrder.h"
#include "../models/OrderBase.h"
#include "../models/Signal.h"
#include "OrderGenerator.h"

namespace sys {
using std::make_shared;

OrderGenerator::OrderGenerator()
    : env(Environment::get_instance()){};

const double OrderGenerator::cur_price(const string &ticker) {
    return env->feeds[ticker]->cur_price();
};

template <typename T>
const bool OrderGenerator::is_buy(const T &signal) {
    return signal->action_type == ActionType::Buy ? true : false;
};
template <typename T>
const bool OrderGenerator::is_sell(const T &signal) {
    return signal->action_type == ActionType::Sell ? true : false;
};
template <typename T>
const bool OrderGenerator::is_short(const T &signal) {
    return signal->action_type == ActionType::Short ? true : false;
};
template <typename T>
const bool OrderGenerator::is_shortcover(const T &signal) {
    return signal->action_type == ActionType::Cover ? true : false;
};
template <typename T>
const bool OrderGenerator::is_absolute_mkt(const T &signal) {
    return typeid(signal) == typeid(SignalByTrigger) ? true : false;
};
template <typename T>
const bool OrderGenerator::is_normal_mkt(const T &signal) {
    return signal.price == 0 ? true : false;
};

template <typename T1, typename T2>
void OrderGenerator::_child_of_mkt(const shared_ptr<T2> &signal,
                                   const int mkt_id,
                                   const string &key,
                                   vector<shared_ptr<PendingOrderBase>> &orders_basket) {
    if (signal->info[key]) {
        T1 order(signal, mkt_id, key);
        orders_basket.push_back(make_shared<T1>(order));
    }
};

template <typename T>
shared_ptr<MarketOrder> OrderGenerator::_generate_mkt_order(const shared_ptr<T> &signal) {
    return make_shared<MarketOrder>(signal, _counter++);
};

template <typename T>
vector<shared_ptr<PendingOrderBase>> OrderGenerator::_generate_child_of_mkt(const int mkt_id,
                                                                     const shared_ptr<T> &signal) {
    vector<shared_ptr<PendingOrderBase>> orders_basket;
    if (is_buy(signal)) {
        _child_of_mkt<StopSellOrder>(signal, mkt_id, "stoploss", orders_basket);
        _child_of_mkt<LimitSellOrder>(signal, mkt_id, "takeprofit", orders_basket);
        _child_of_mkt<TrailingStopSellOrder>(signal, mkt_id, "trailingstop", orders_basket);
        _child_of_mkt<StopSellOrder>(signal, mkt_id, "stoploss_pct", orders_basket);
        _child_of_mkt<LimitSellOrder>(signal, mkt_id, "takeprofit_pct", orders_basket);
        _child_of_mkt<TrailingStopSellOrder>(signal, mkt_id, "trailingstop_pct", orders_basket);
    } else {
        _child_of_mkt<StopCoverOrder>(signal, mkt_id, "stoploss", orders_basket);
        _child_of_mkt<LimitCoverOrder>(signal, mkt_id, "takeprofit", orders_basket);
        _child_of_mkt<TrailingStopCoverOrder>(signal, mkt_id, "trailingstop", orders_basket);
        _child_of_mkt<StopCoverOrder>(signal, mkt_id, "stoploss_pct", orders_basket);
        _child_of_mkt<LimitCoverOrder>(signal, mkt_id, "takeprofit_pct", orders_basket);
        _child_of_mkt<TrailingStopCoverOrder>(signal, mkt_id, "trailingstop_pct", orders_basket);
    }

    return orders_basket;
};

template <typename T>
shared_ptr<PendingOrderBase> OrderGenerator::_generate_pending_order(const shared_ptr<T> &signal) {
    shared_ptr<PendingOrderBase> order;

    if (signal->info["price"] > cur_price(signal->ticker)) {
        if (is_buy(signal))
            order = make_shared<StopBuyOrder>(signal, 0, "price");
        else if (is_shortcover(signal))
            order = make_shared<StopCoverOrder>(signal, 0, "price");
        else if (is_sell(signal))
            order = make_shared<LimitSellOrder>(signal, 0, "price");
        else if (is_short(signal))
            order = make_shared<LimitShortOrder>(signal, 0, "price");
    } else if (signal->info["price"] < cur_price(signal->ticker)) {
        if (is_buy(signal))
            order = make_shared<LimitBuyOrder>(signal, 0, "price");
        else if (is_shortcover(signal))
            order = make_shared<LimitCoverOrder>(signal, 0, "price");
        else if (is_sell(signal))
            order = make_shared<StopSellOrder>(signal, 0, "price");
        else if (is_short(signal))
            order = make_shared<StopShortOrder>(signal, 0, "price");

    } else {
        throw std::logic_error("Here shouldn't be raised");
    }
    return order;
};
void OrderGenerator::submit_mkt_order_with_child(
    shared_ptr<MarketOrder> &mkt_order,
    const vector<shared_ptr<PendingOrderBase>> &orders_basket,
    vector<shared_ptr<MarketOrder>> &orders_cur) {
    orders_cur.push_back(mkt_order);
    if (orders_basket.size() != 0) {
        env->orders_child_of_mkt_dict[mkt_order->mkt_id] = orders_basket;
    }
};

void OrderGenerator::_process_mkt_signals() {
    for (auto &signal : env->signals_normal_cur) {
        auto mkt_order = _generate_mkt_order(signal);
        auto child_of_mkt = _generate_child_of_mkt(mkt_order->mkt_id, signal);
        submit_mkt_order_with_child(
            mkt_order, child_of_mkt, env->orders_mkt_normal_cur);
    }
};

void OrderGenerator::_process_triggered_signals() {
    for (auto &signal : env->signals_trigger_cur) {
        auto mkt_order = _generate_mkt_order(signal);
        auto child_of_mkt = _generate_child_of_mkt(mkt_order->mkt_id, signal);
        submit_mkt_order_with_child(
            mkt_order, child_of_mkt, env->orders_mkt_absolute_cur);
    };
}

void OrderGenerator::_process_pending_signals() {
    for (auto &signal : env->signals_pending_cur) {
        auto pending_order = _generate_pending_order(signal);
        env->orders_pending.push_back(pending_order);
    };
}

void OrderGenerator::_process_cancel_signals() {
    for (auto &signal : env->signals_cancel_tst_cur)
        env->orders_cancel_cur.push_back(make_shared<CancelTSTOrder>(signal));
    for (auto &signal : env->signals_cancel_pending_cur)
        env->orders_cancel_cur.push_back(make_shared<CancelPendingOrder>(signal));
};

void OrderGenerator::_clear_current_signals_memory() {
    env->signals_normal_cur.clear();
    env->signals_pending_cur.clear();
    env->signals_trigger_cur.clear();
    env->signals_cancel_tst_cur.clear();
    env->signals_cancel_pending_cur.clear();
};

void OrderGenerator::run() {
    _process_mkt_signals();
    _process_triggered_signals();
    _process_pending_signals();
    _process_cancel_signals();
    _clear_current_signals_memory();
};

} // namespace sys
