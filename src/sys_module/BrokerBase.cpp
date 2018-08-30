#include "../Environment.h"
#include "BrokerBase.h"
#include "components/OrderChencker.h"
#include "components/OrderGenerator.h"

namespace sys {
using std::make_shared;

BrokerBase::BrokerBase()
    : env(Environment::get_instance()),
      _order_generator(make_shared<OrderGenerator>()){};

template <typename broker_name>
void BrokerBase::save_to_env(const broker_name *self_ptr) {
    env->brokers["Broker"] = make_shared<broker_name>(*self_ptr); //TODO:设置名字
}

void BrokerBase::_clear_submitted_order() {
    env->orders_mkt_submitted_cur.clear();
    env->orders_cancel_cur.clear();
};

void BrokerBase::_generate_order() {
    _order_generator->run();
};

void BrokerBase::_check_order() {
    _checker->run();
};

void BrokerBase::_submit_order() {
    _process_cancel_order();
};

void BrokerBase::_judge_long_or_short(){

};

void BrokerBase::_process_cancel_order(){};

void BrokerBase::run() {
    _clear_submitted_order();
    _generate_order();
    _check_order();
    _submit_order();
};

} // namespace sys
