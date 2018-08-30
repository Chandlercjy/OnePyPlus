#include "../../Constants.h"
#include "../../Environment.h"
#include "../models/PendingOrderBase.h"
#include "PendingOrderChecker.h"
#include "TriggeredSignalGenerator.h"

namespace sys {

PendingOrderChecker::PendingOrderChecker()
    : env(Environment::get_instance()){};

void PendingOrderChecker::_check_orders_pending() {
    auto it = env->orders_pending.cbegin();
    const int size = env->orders_pending.size();
    for (int a = 0; a < size; a++) {
        if (TriggeredSignalGenerator::generate_triggered_signal(*it)) {
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
            if (TriggeredSignalGenerator::generate_triggered_signal(order)) {
                order->set_status(OrderStatus::Triggered);
                //env->orders_child_of_mkt_dict.erase();
                delete_record.push_back(elem.first);
                break;
            }
        }
    }
    for (auto &key : delete_record)
        env->orders_child_of_mkt_dict.erase(key);
};

void PendingOrderChecker::run() {
    _check_orders_pending();
    _check_orders_pending_with_mkt();
};
} // namespace sys
