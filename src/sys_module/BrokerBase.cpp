#include "Constants.h"
#include "Environment.h"
#include "sys_module/BrokerBase.h"
#include "sys_module/components/OrderGenerator.h"
#include "sys_module/components/SubmitOrderChecker.h"
#include "sys_module/models/GeneralOrder.h"

OP_NAMESPACE_START

BrokerBase::BrokerBase()
    : env(Environment::get_instance()),
      _order_generator(make_shared<OrderGenerator>()){};

template <typename T>
void BrokerBase::save_to_env(const T *self_ptr, const string &name) {
    env->brokers[name] = make_shared<T>(*self_ptr); //TODO:设置名字
}

void BrokerBase::_clear_submitted_order() {
    env->orders_mkt_submitted_cur.clear();
    env->orders_cancel_tst_cur.clear();
    env->orders_cancel_pending_cur.clear();
};

void BrokerBase::_generate_order() {
    _order_generator->run();
};

void BrokerBase::_check_order() {
    _checker->run();
};

void BrokerBase::_submit_order() {
    _process_cancel_tst_order();
    _process_cancel_pending_order();
};

const string BrokerBase::_judge_long_or_short(const ActionType &action_type) {
    if (action_type == ActionType::Buy || action_type == ActionType::Sell)
        return "long";
    else if (action_type == ActionType::Short || action_type == ActionType::Cover)
        return "short";
    else
        throw std::logic_error("Never Raised");
};

void BrokerBase::_process_cancel_pending_order() {

    for (auto &cancel_order : env->orders_cancel_pending_submitted) {
        auto ticker = cancel_order->ticker;
        auto long_or_short = cancel_order->long_or_short;

        auto it = env->orders_pending.cbegin();
        const auto size = env->orders_pending.size();
        for (int a = 0; a < size; a++) {
            auto &order = *it;
            auto confirm_ticker = (order->ticker == ticker);
            auto confirm_long_short = (_judge_long_or_short(
                                           order->get_action_type()) == long_or_short);

            if (confirm_ticker && confirm_long_short) {
                if (cancel_order->is_target(order->target_price()))
                    env->orders_pending.erase(it);
            } else
                it++;
        }
    }
}

void BrokerBase::_process_cancel_tst_order() {

    for (auto &cancel_order : env->orders_cancel_tst_submitted) {
        for (auto &order_list : env->orders_child_of_mkt_dict) {
            auto it = order_list.second.cbegin();

            for (auto &order : order_list.second)
                if (cancel_order->is_target(order->trigger_key))
                    order_list.second.erase(it);
                else
                    it++;
        }
    }
}

void BrokerBase::run() {
    _clear_submitted_order();
    _generate_order();
    _check_order();
    _submit_order();
};

OP_NAMESPACE_END


