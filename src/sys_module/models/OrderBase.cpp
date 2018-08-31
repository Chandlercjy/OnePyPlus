#include "Constants.h"
#include "Environment.h"
#include "sys_module/models/BarBase.h"
#include "sys_module/models/OrderBase.h"
#include "sys_module/models/Signal.h"

namespace sys {

template <typename T>
OrderBase::OrderBase(const shared_ptr<T> &signal,
                     const int mkt_id)
    : env(Environment::get_instance()),
      strategy_name(signal->strategy_name),
      ticker(signal->ticker),
      size(signal->size),
      trading_date(signal->datetime),
      order_id(_counter++),
      mkt_id(mkt_id)

{
    set_status(OrderStatus::Created);
    set_first_cur_price_and_signal_type(signal);
    _save_signal_info(signal);
};

void OrderBase::set_status(const OrderStatus &value) {
    _status = value;
};

const OrderStatus OrderBase::get_status() const {
    return _status;
};

template <typename T>
void OrderBase::set_first_cur_price_and_signal_type(const shared_ptr<T> &signal) {
    _first_cur_price = env->feeds[ticker]->execute_price();
    _signal_type = "normal";
};

template <>
void OrderBase::set_first_cur_price_and_signal_type(const shared_ptr<SignalByTrigger> &signal) {
    _first_cur_price = signal->execute_price;
    _signal_type = "triggered";
};

const double OrderBase::get_first_cur_price() const {
    return _first_cur_price;
};

const string OrderBase::get_signal_type() const {
    return _signal_type;
};

template <typename T>
void OrderBase::_save_signal_info(const T &signal) {
    signal_info["price"] = signal->price;
    signal_info["takeprofit"] = signal->takeprofit;
    signal_info["takeprofit_pct"] = signal->takeprofit_pct;
    signal_info["stoploss"] = signal->stoploss;
    signal_info["stoploss_pct"] = signal->stoploss_pct;
    signal_info["trailingstop"] = signal->trailingstop;
    signal_info["trailingstop_pct"] = signal->trailingstop_pct;
};

} // namespace sys
