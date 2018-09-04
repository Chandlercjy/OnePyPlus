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
      datetime(env->sys_date) {
    _record_info(info);
};

void SignalBase::_record_info(map<string, double> info) {
    size = info["size"];
    price = info["price"];
    takeprofit = info["takeprofit"];
    takeprofit_pct = info["takeprofit_pct"];
    stoploss = info["stoploss"];
    stoploss_pct = info["stoploss_pct"];
    trailingstop = info["trailingstop"];
    trailingstop_pct = info["trailingstop_pct"];
};

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
    const double first_cur_price,
    const double parent_order_difference)

    : SignalBase(info, ticker, strategy_name, action_type),
      order_type(order_type),
      mkt_id(mkt_id),
      trigger_key(trigger_key),
      execute_price(execute_price),
      first_cur_price(first_cur_price),
      parent_order_difference(parent_order_difference),
      signal_id(Counter::update_signal_by_trigger_id()){};

OP_NAMESPACE_END
