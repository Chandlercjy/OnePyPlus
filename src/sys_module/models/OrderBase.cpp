#include "Constants.h"
#include "Environment.h"
#include "sys_module/models/BarBase.h"
#include "sys_module/models/Counter.h"
#include "sys_module/models/OrderBase.h"
#include "sys_module/models/Signal.h"

OP_NAMESPACE_START

OrderBase::OrderBase(const shared_ptr<SignalBase> &signal,
                     const int mkt_id)
    : env(Environment::get_instance()),
      strategy_name(signal->strategy_name),
      ticker(signal->ticker),
      size(signal->size()),
      trading_date(signal->datetime),
      order_id(Counter::update_order_id()),
      mkt_id(mkt_id),
      signal_info(signal->info),
      _signal_type("normal"),
      _first_cur_price(env->feeds[ticker]->execute_price())

{
    set_status(OrderStatus::Created);
    //set_first_cur_price_and_signal_type(signal);
};


void OrderBase::set_first_cur_price_and_signal_type(const shared_ptr<SignalBase> &signal) {
    _first_cur_price = env->feeds[ticker]->execute_price();
    _signal_type = "normal";
};

//void OrderBase::set_first_cur_price_and_signal_type_trigger(const shared_ptr<SignalByTrigger> &signal) {
//_first_cur_price = signal->execute_price;
//_signal_type = "triggered";
//};
//
void OrderBase::set_status(const OrderStatus &value) {
    _status = value;
};

const OrderStatus OrderBase::get_status() const {
    return _status;
};

const double OrderBase::get_first_cur_price() const {
    return _first_cur_price;
};

const string OrderBase::get_signal_type() const {
    return _signal_type;
};

OP_NAMESPACE_END
