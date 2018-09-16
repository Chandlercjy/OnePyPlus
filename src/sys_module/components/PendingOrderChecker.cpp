#include "Constants.h"
#include "Environment.h"
#include "sys_module/components/PendingOrderChecker.h"
#include "sys_module/components/TriggeredSignalGenerator.h"
#include "sys_module/models/PendingOrder.h"

OP_NAMESPACE_START

PendingOrderChecker::PendingOrderChecker()
    : env(Environment::get_instance()),
      _triggered_signal_generator(make_shared<TriggeredSignalGenerator>()){};

void PendingOrderChecker::_check_orders_pending() {
    auto it = env->orders_pending.cbegin();
    const int size = env->orders_pending.size();
    for (int a = 0; a < size; a++) {
        if (_triggered_signal_generator->generate_triggered_signal(*it)) {
            (*it)->set_status(OrderStatus::Triggered);
            env->orders_pending.erase(it); // 成交的单子需要删除
        } else {
            it++;
        }
    }
};
void PendingOrderChecker::_check_orders_pending_with_mkt() {
    vector<int> delete_record = {};

    for (auto &elem : env->orders_child_of_mkt_dict) {
        for (auto &order : elem.second) {
            if (_triggered_signal_generator->generate_triggered_signal(order)) {
                order->set_status(OrderStatus::Triggered);
                delete_record.push_back(elem.first);
                break;
            }
        }
    }
    //批量删除已被触发的child
    for (auto &key : delete_record)
        env->orders_child_of_mkt_dict.erase(key);
};

void PendingOrderChecker::run() {
    _check_orders_pending();
    _check_orders_pending_with_mkt();
};
OP_NAMESPACE_END
