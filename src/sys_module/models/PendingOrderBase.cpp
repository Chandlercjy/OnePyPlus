#include "Environment.h"
#include "sys_module/models/BarBase.h"
#include "sys_module/models/Counter.h"
#include "sys_module/models/PendingOrderBase.h"
#include "sys_module/models/Signal.h"

OP_NAMESPACE_START

PendingOrderBase::PendingOrderBase(const shared_ptr<SignalBase> &signal,
                                   const int mkt_id,
                                   const string &trigger_key)
    : env(Environment::get_instance()),
      strategy_name(signal->strategy_name),
      ticker(signal->ticker),
      size(signal->size()),
      trading_date(signal->datetime),
      order_id(Counter::update_order_id()),
      mkt_id(mkt_id),
      signal_info(signal->info),
      trigger_key(trigger_key),
      _signal_type("normal"),
      _first_cur_price(env->feeds[ticker]->execute_price()){};

PendingOrderBase::PendingOrderBase(const SignalByTriggerPtr &signal,
                                   const int mkt_id,
                                   const string &trigger_key)
    : env(Environment::get_instance()),
      strategy_name(signal->strategy_name),
      ticker(signal->ticker),
      size(signal->size()),
      trading_date(signal->datetime),
      order_id(Counter::update_order_id()),
      mkt_id(mkt_id),
      signal_info(signal->info),
      trigger_key(trigger_key),
      _signal_type("triggered"),
      _first_cur_price(signal->execute_price){};

const double PendingOrderBase::cur_open() const {
    return env->feeds[ticker]->open();
};
const double PendingOrderBase::cur_high() const {
    return env->feeds[ticker]->high();
};

const double PendingOrderBase::cur_low() const {
    return env->feeds[ticker]->low();
};

const double PendingOrderBase::difference() {
    if (trigger_key.find("pct") == string::npos)
        return signal_info[trigger_key] / size;
    return signal_info[trigger_key] * _first_cur_price;
};

const double PendingOrderBase::cur_high_cross_target_price() {
    return target_price() < cur_high() ? true : false;
};
const double PendingOrderBase::cur_low_cross_target_price() {
    return target_price() > cur_low() ? true : false;
};
const bool PendingOrderBase::is_with_mkt() {
    return trigger_key == "price" ? false : true; //判断是否是跟随市价单的挂单
};
const double PendingOrderBase::below_price(const double diff) {
    return _first_cur_price - diff;
};
const double PendingOrderBase::above_price(const double diff) {
    return _first_cur_price + diff;
};

const double PendingOrderBase::target_price() {
    if (trigger_key == "price")
        return signal_info[trigger_key];
    else if (target_below())
        below_price(difference());
    return above_price(difference());
};

const bool PendingOrderBase::is_triggered() {
    if (target_below())
        return cur_low_cross_target_price();
    return cur_high_cross_target_price();
};

void PendingOrderBase::set_status(const OrderStatus &value) {
    _status = value;
};

const OrderStatus PendingOrderBase::get_status() const {
    return _status;
};

const double PendingOrderBase::get_first_cur_price() const {
    return _first_cur_price;
};

const string PendingOrderBase::get_signal_type() const {
    return _signal_type;
};

OP_NAMESPACE_END
