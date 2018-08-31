#include "Constants.h"
#include "Environment.h"
#include "sys_module/RecorderBase.h"
#include "sys_module/components/SubmitOrderChecker.h"
#include "sys_module/models/GeneralOrder.h"
#include "sys_module/models/SeriesBase.h"
#include "utils/utils.h"

namespace sys {

using Cash_func_ptr_type = double (*)(const shared_ptr<MarketOrder> &order);
SubmitOrderChecker::SubmitOrderChecker(Cash_func_ptr_type cash_func_ptr)
    : env(Environment::get_instance()),
      required_cash_func(cash_func_ptr){};

double SubmitOrderChecker::cur_cash() {
    return env->recorder->cash->latest();
};

double SubmitOrderChecker::cur_position(const string &ticker,
                                        const ActionType &action_type) {
    if (action_type == ActionType::Sell)
        return env->recorder->position->latest(ticker, "long");
    else if (action_type == ActionType::Cover)
        return env->recorder->position->latest(ticker, "short");
    else
        throw std::logic_error("Never Raised");
};

double SubmitOrderChecker::required_cash(const shared_ptr<MarketOrder> &order) {
    return (*required_cash_func)(order);
};

double SubmitOrderChecker::_acumu_position(const string &ticker,
                                           const ActionType &action_type) {
    if (action_type == ActionType::Sell)
        return env->recorder->position->latest(ticker, "long");
    else if (action_type == ActionType::Cover)
        return env->recorder->position->latest(ticker, "short");
    else
        throw std::logic_error("Never Raised");
};

void SubmitOrderChecker::order_pass_checker(const shared_ptr<MarketOrder> &order) {
    order->set_status(OrderStatus::Submitted);
    env->orders_mkt_submitted_cur.push_back(order);
};

bool SubmitOrderChecker::_is_partial(const shared_ptr<MarketOrder> &order,
                                     const double cur_pos,
                                     const double acumu_pos) {

    const auto &diff = cur_pos - (acumu_pos - order->size);

    if (diff > 0) {
        order->size = diff;
        order->set_status(OrderStatus::Partial);
        return true;
    }
    return false;
};

bool SubmitOrderChecker::_lack_of_cash() {
    return cash_acumu > cur_cash() ? true : false;
};

bool SubmitOrderChecker::_lack_of_position(const double cur_pos, const double acumu_pos) {
    if (cur_pos == 0 || acumu_pos > cur_pos)
        return true;
    return false;
};

void SubmitOrderChecker::_add_to_cash_cumu(const shared_ptr<MarketOrder> &order) {
    cash_acumu += required_cash(order);
};
void SubmitOrderChecker::_add_to_position_cumu(const shared_ptr<MarketOrder> &order) {
    if (order->get_action_type() == ActionType::Sell)
        plong_acumu[order->ticker] += order->size;
    else if (order->get_action_type() == ActionType::Cover)
        pshort_acumu[order->ticker] += order->size;
    else
        throw std::logic_error("Never Raised");
};
void SubmitOrderChecker::_delete_from_cash_cumu(const shared_ptr<MarketOrder> &order) {
    cash_acumu -= required_cash(order);
};
void SubmitOrderChecker::_delete_from_position_cumu(const shared_ptr<MarketOrder> &order) {
    if (order->get_action_type() == ActionType::Sell)
        plong_acumu[order->ticker] -= order->size;
    else if (order->get_action_type() == ActionType::Cover)
        pshort_acumu[order->ticker] -= order->size;
    else
        throw std::logic_error("Never Raised");
};

void SubmitOrderChecker::_make_position_cumu_full(const string &ticker,
                                                  const ActionType &action_type) {
    if (action_type == ActionType::Sell)
        plong_acumu[ticker] = cur_position(ticker, action_type);
    else if (action_type == ActionType::Cover)
        pshort_acumu[ticker] = cur_position(ticker, action_type);
    else
        throw std::logic_error("Never Raised");
};

void SubmitOrderChecker::_check(const OrderBox<MarketOrder> order_list) {
    for (auto &order : order_list) {
        const auto &ticker = order->ticker;
        const auto &action_type = order->get_action_type();

        if (action_type == ActionType::Buy || action_type == ActionType::Short) {
            _add_to_cash_cumu(order);

            if (_lack_of_cash()) {
                //self.env.logger.warning("Cash is not enough for trading!")//TODO
                order->set_status(OrderStatus::Rejected);
                _delete_from_cash_cumu(order);

                if (utils::is_elem_in_map_key(env->orders_child_of_mkt_dict, order->mkt_id))
                    env->orders_child_of_mkt_dict.erase(order->mkt_id);

                continue;
            }
        } else if (action_type == ActionType::Sell || action_type == ActionType::Cover) {
            _add_to_position_cumu(order);

            auto cur_pos = cur_position(ticker, action_type);
            auto acumu_position = _acumu_position(ticker, action_type);

            if (_lack_of_position(cur_pos, acumu_position)) {
                if (_is_partial(order, cur_pos, acumu_position)) {
                    _make_position_cumu_full(ticker, action_type);
                } else {
                    order->set_status(OrderStatus::Rejected);
                    _delete_from_position_cumu(order);

                    continue;
                }
            }
        }

        order_pass_checker(order);
    }
};

void SubmitOrderChecker::_check_market_order() {
    cash_acumu = 0;
    plong_acumu = {};
    pshort_acumu = {};
    _check(env->orders_mkt_absolute_cur);
    _check(env->orders_mkt_normal_cur);
};

void SubmitOrderChecker::_check_pending_order(){};

void SubmitOrderChecker::_check_cancel_order() {
    for (auto &order : env->orders_cancel_tst_cur)
        order->set_status(OrderStatus::Submitted);
    env->orders_cancel_tst_submitted = env->orders_cancel_tst_cur;

    for (auto &order : env->orders_cancel_pending_cur)
        order->set_status(OrderStatus::Submitted);
    env->orders_cancel_pending_submitted = env->orders_cancel_pending_cur;
};
void SubmitOrderChecker::_clear_all_cur_order() {
    env->orders_mkt_absolute_cur.clear();
    env->orders_mkt_normal_cur.clear();
    env->orders_cancel_tst_cur.clear();
    env->orders_cancel_pending_cur.clear();
};

void SubmitOrderChecker::run() {
    _check_market_order();
    _check_pending_order();
    _check_cancel_order();
    _clear_all_cur_order();
};

} // namespace sys
