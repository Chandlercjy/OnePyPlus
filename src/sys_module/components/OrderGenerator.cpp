#include "Constants.h"
#include "DataType.h"
#include "sys_module/components/OrderGenerator.h"
#include "sys_module/models/Counter.h"
#include "sys_module/models/GeneralOrder.h"
#include "sys_module/models/OrderBase.h"
#include "sys_module/models/Signal.h"

OP_NAMESPACE_START

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

template <typename T>
void OrderGenerator::_child_of_mkt(const ActionType &action_type,
                                   const OrderType &order_type,
                                   const shared_ptr<T> &signal,
                                   const int mkt_id,
                                   const string &key,
                                   vector<shared_ptr<PendingOrder>> &orders_basket) {
    if (signal->info[key]) {
        orders_basket.push_back(make_shared<PendingOrder>(
            action_type, order_type, signal, mkt_id, key));
    }
};

template <typename T>
MarketOrderPtr OrderGenerator::_generate_mkt_order(const shared_ptr<T> &signal) {
    return make_shared<MarketOrder>(signal, Counter::update_mkt_id());
};

template <typename T>
vector<shared_ptr<PendingOrder>> OrderGenerator::_generate_child_of_mkt(const int mkt_id,
                                                                        const shared_ptr<T> &signal) {
    vector<shared_ptr<PendingOrder>> orders_basket;
    if (is_buy(signal)) {
        _child_of_mkt(ActionType::Sell, OrderType::Limit, signal, mkt_id, "takeprofit", orders_basket);
        _child_of_mkt(ActionType::Sell, OrderType::Limit, signal, mkt_id, "takeprofit_pct", orders_basket);
        _child_of_mkt(ActionType::Sell, OrderType::Stop, signal, mkt_id, "stoploss", orders_basket);
        _child_of_mkt(ActionType::Sell, OrderType::Stop, signal, mkt_id, "stoploss_pct", orders_basket);
        _child_of_mkt(ActionType::Sell, OrderType::Trailing_stop, signal, mkt_id, "trailingstop", orders_basket);
        _child_of_mkt(ActionType::Sell, OrderType::Trailing_stop, signal, mkt_id, "trailingstop_pct", orders_basket);
    } else {
        _child_of_mkt(ActionType::Cover, OrderType::Limit, signal, mkt_id, "takeprofit", orders_basket);
        _child_of_mkt(ActionType::Cover, OrderType::Limit, signal, mkt_id, "takeprofit_pct", orders_basket);
        _child_of_mkt(ActionType::Cover, OrderType::Stop, signal, mkt_id, "stoploss", orders_basket);
        _child_of_mkt(ActionType::Cover, OrderType::Stop, signal, mkt_id, "stoploss_pct", orders_basket);
        _child_of_mkt(ActionType::Cover, OrderType::Trailing_stop, signal, mkt_id, "trailingstop", orders_basket);
        _child_of_mkt(ActionType::Cover, OrderType::Trailing_stop, signal, mkt_id, "trailingstop_pct", orders_basket);
    }

    return orders_basket;
};

template <typename T>
shared_ptr<PendingOrder> OrderGenerator::_generate_pending_order(const shared_ptr<T> &signal) {
    shared_ptr<PendingOrder> order;

    if (signal->info["price"] > cur_price(signal->ticker)) {
        if (is_buy(signal))
            order = make_shared<PendingOrder>(ActionType::Buy, OrderType::Stop, signal, 0, "price");
        else if (is_shortcover(signal))
            order = make_shared<PendingOrder>(ActionType::Cover, OrderType::Stop, signal, 0, "price");
        else if (is_sell(signal))
            order = make_shared<PendingOrder>(ActionType::Sell, OrderType::Limit, signal, 0, "price");
        else if (is_short(signal))
            order = make_shared<PendingOrder>(ActionType::Short, OrderType::Limit, signal, 0, "price");
    } else if (signal->info["price"] < cur_price(signal->ticker)) {
        if (is_buy(signal))
            order = make_shared<PendingOrder>(ActionType::Buy, OrderType::Limit, signal, 0, "price");
        else if (is_shortcover(signal))
            order = make_shared<PendingOrder>(ActionType::Cover, OrderType::Limit, signal, 0, "price");
        else if (is_sell(signal))
            order = make_shared<PendingOrder>(ActionType::Sell, OrderType::Stop, signal, 0, "price");
        else if (is_short(signal))
            order = make_shared<PendingOrder>(ActionType::Short, OrderType::Stop, signal, 0, "price");
    } else {
        throw std::logic_error("Here shouldn't be raised");
    }
    return order;
};
void OrderGenerator::submit_mkt_order_with_child(
    MarketOrderPtr &mkt_order,
    const vector<shared_ptr<PendingOrder>> &orders_basket,
    vector<MarketOrderPtr> &orders_cur) {
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
        env->orders_cancel_tst_cur.push_back(make_shared<CancelTSTOrder>(signal));
    for (auto &signal : env->signals_cancel_pending_cur)
        env->orders_cancel_pending_cur.push_back(make_shared<CancelPendingOrder>(signal));
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

OP_NAMESPACE_END
