#include "Environment.h"
#include "Exceptions.h"
#include "sys_module/models/BarBase.h"
#include "sys_module/models/Counter.h"
#include "sys_module/models/Signal.h"

OP_NAMESPACE_START

SignalBase::SignalBase(
    const map<string, double> &info,
    const string &ticker,
    const string &strategy_name,
    const ActionType &action_type)
    : env(Environment::get_instance()),
      info(info),
      ticker(ticker),
      strategy_name(strategy_name),
      action_type(action_type),
      datetime(env->sys_date){};

double SignalBase::size() {
    return info["size"];
}
double SignalBase::price() {
    return info["price"];
}
double SignalBase::takeprofit() {
    return info["takeprofit"];
}
double SignalBase::takeprofit_pct() {
    return info["takeprofit_pct"];
}
double SignalBase::stoploss() {
    return info["stoploss"];
}
double SignalBase::stoploss_pct() {
    return info["stoploss_pct"];
}
double SignalBase::trailingstop() {
    return info["trailingstop"];
}
double SignalBase::trailingstop_pct() {
    return info["trailingstop_pct"];
}

Signal::Signal(const map<string, double> &info,
               const string &ticker,
               const string &strategy_name,
               const ActionType &action_type)

    : SignalBase(info, ticker, strategy_name, action_type),
      signal_id(Counter::update_signal_id()){};

SignalForPending::SignalForPending(
    const map<string, double> &info,
    const string &ticker,
    const string &strategy_name,
    const ActionType &action_type)

    : SignalBase(info, ticker, strategy_name, action_type),
      signal_id(Counter::update_signal_id()){};

SignalByTrigger::SignalByTrigger(
    const map<string, double> &info,
    const string &ticker,
    const string &strategy_name,
    const ActionType &action_type,
    const OrderType &order_type,
    const int mkt_id,
    const string &trigger_key,
    const double execute_price,
    const double cur_price_when_generated,
    const double parent_order_difference)

    : SignalBase(info, ticker, strategy_name, action_type),
      order_type(order_type),
      mkt_id(mkt_id),
      trigger_key(trigger_key),
      execute_price(execute_price),
      cur_price_when_generated(cur_price_when_generated),
      parent_order_difference(parent_order_difference),
      signal_id(Counter::update_signal_by_trigger_id()){};

OP_NAMESPACE_END
