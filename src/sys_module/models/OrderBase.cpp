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
      trading_date(env->feeds[signal->ticker]->next_date()),
      order_id(Counter::update_order_id()),
      mkt_id(mkt_id),
      signal_info(signal->info),
      from_signal_type("normal"),
      from_order_type(OrderType::Market),
      _cur_price_when_generated(env->feeds[ticker]->execute_price())

{
    set_status(OrderStatus::Created);
    //set_cur_price_when_generated_and_signal_type(signal);
};

OrderBase::OrderBase(const shared_ptr<SignalByTrigger> &signal,
                     const int mkt_id)
    : env(Environment::get_instance()),
      strategy_name(signal->strategy_name),
      ticker(signal->ticker),
      size(signal->size()),
      trading_date(signal->datetime),
      order_id(Counter::update_order_id()),
      mkt_id(mkt_id),
      signal_info(signal->info),
      from_signal_type("triggered"),
      from_order_type(signal->order_type),
      _cur_price_when_generated(signal->execute_price)

{
    set_status(OrderStatus::Created);
    //set_cur_price_when_generated_and_signal_type(signal);
};

//void OrderBase::set_cur_price_when_generated_and_signal_type(const shared_ptr<SignalBase> &signal) {
    //_cur_price_when_generated = env->feeds[ticker]->execute_price();
    //from_signal_type = "normal";
//};

//void OrderBase::set_cur_price_when_generated_and_signal_type_trigger(const shared_ptr<SignalByTrigger> &signal) {
    //_cur_price_when_generated = signal->execute_price;
    //from_signal_type = "triggered";
//};

void OrderBase::set_status(const OrderStatus &value) {
    _status = value;
};

const OrderStatus OrderBase::get_status() const {
    return _status;
};

const double OrderBase::get_cur_price_when_generated() const {
    return _cur_price_when_generated;
};

const string OrderBase::get_signal_type() const {
    return from_signal_type;
};

OP_NAMESPACE_END
