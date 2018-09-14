#include "Environment.h"
#include "sys_module/components/MatchEngine.h"
#include "sys_module/components/TradeLogGenerator.h"
#include "sys_module/models/GeneralOrder.h"
#include "utils/utils.h"

OP_NAMESPACE_START

using namespace utils;

MatchEngine::MatchEngine()
    : env(Environment::get_instance()),
      log_generator(make_shared<TradeLogGenerator>()) {}

void MatchEngine::_append_finished(MarketOrderPtr &buy_order,
                                   MarketOrderPtr &sell_order,
                                   const double size) {
    finished_log.emplace_back(log_generator->make_log(buy_order,
                                                      sell_order,
                                                      size));
}

void MatchEngine::_search_father(MarketOrderPtr &order,
                                 vector<MarketOrderPtr> &log_with_trigger) {
    for (auto &log : log_with_trigger) {
        if (log->mkt_id == order->father_mkt_id) {
            _append_finished(log, order, order->size);
            log_with_trigger.erase(std::remove(log_with_trigger.begin(),
                                               log_with_trigger.end(),
                                               log));
            break;
        }
    }
}
void MatchEngine::_del_in_mkt_dict(const int mkt_id) {
    if (Stl::is_elem_in_map_key(env->orders_child_of_mkt_dict, mkt_id))
        env->orders_child_of_mkt_dict.erase(mkt_id);
}
void MatchEngine::_change_order_size_in_pending_mkt_dict(const int mkt_id,
                                                         const double track_size) {
    if (Stl::is_elem_in_map_key(env->orders_child_of_mkt_dict, mkt_id))
        for (auto &pending_order : env->orders_child_of_mkt_dict[mkt_id])
            pending_order->size = track_size;
}
void MatchEngine::_pair_one_by_one(PtrBox<MarketOrderPtr> &order_list,
                                   double sell_size,
                                   MarketOrderPtr &order,
                                   const bool counteract) {
    if (order_list.empty()) {
        auto &log_with_trigger = (order->long_or_short == "long")
                                     ? long_log_with_trigger[order->ticker]
                                     : short_log_with_trigger[order->ticker];
        _pair_one_by_one(log_with_trigger, sell_size, order, true);
    } else {
        MarketOrderPtr &buy_order = order_list[0];
        double buy_size = buy_order->track_size;
        double diff = buy_size - sell_size;
        buy_order->track_size = diff;

        if (diff > 0) {
            _append_finished(buy_order, order, sell_size);

            if (counteract) // 修改dict中订单size
                _change_order_size_in_pending_mkt_dict(
                    buy_order->mkt_id, buy_order->track_size);
        } else if (diff == 0) {
            _append_finished(buy_order, order, sell_size);
            order_list.erase(order_list.cbegin());

            if (counteract)
                _del_in_mkt_dict(buy_order->mkt_id);
        } else {
            _append_finished(buy_order, order, buy_size);
            order_list.erase(order_list.cbegin());
            sell_size -= buy_size;

            if (counteract)
                _del_in_mkt_dict(buy_order->mkt_id);
            _pair_one_by_one(order_list, sell_size, order);
        }
    }
}

void MatchEngine::_pair_order(const string &long_or_short,
                              MarketOrderPtr &order) {
    auto &log_pure = (long_or_short == "long")
                         ? long_log_pure[order->ticker]
                         : short_log_pure[order->ticker];
    auto &log_with_trigger = (order->long_or_short == "long")
                                 ? long_log_with_trigger[order->ticker]
                                 : short_log_with_trigger[order->ticker];

    double sell_size = order->size;

    if (order->from_signal_type == "triggered")
        _search_father(order, log_with_trigger);
    else
        _pair_one_by_one(log_pure, sell_size, order);
}
void MatchEngine::match_order(MarketOrderPtr &order) {
    if (order->action_type == ActionType::Buy) {
        order->track_size = order->size;
        if (order->is_pure())
            long_log_pure[order->ticker].emplace_back(order);
        else
            long_log_with_trigger[order->ticker].emplace_back(order);
    } else if (order->action_type == ActionType::Short) {
        order->track_size = order->size;
        if (order->is_pure())
            short_log_pure[order->ticker].emplace_back(order);
        else
            short_log_with_trigger[order->ticker].emplace_back(order);

    } else {
        _pair_order(order->long_or_short, order);
    }
}

void MatchEngine::append_left_trade_to_log() {
    for (auto &ticker : env->tickers) {
        for (auto &order : long_log_pure[ticker])
            settle_left_trade(order, order->track_size);
        for (auto &order : long_log_with_trigger[ticker])
            settle_left_trade(order, order->track_size);
        for (auto &order : short_log_pure[ticker])
            settle_left_trade(order, order->track_size);
        for (auto &order : short_log_with_trigger[ticker])
            settle_left_trade(order, order->track_size);
    }
}

void MatchEngine::settle_left_trade(MarketOrderPtr &unfinished_order, const double size) {
    finished_log.emplace_back(log_generator->settle_left_trade(unfinished_order,
                                                               size));
}

OP_NAMESPACE_END
