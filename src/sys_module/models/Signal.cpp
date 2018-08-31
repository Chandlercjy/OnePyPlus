#include "Environment.h"
#include "Exceptions.h"
#include "sys_module/models/BarBase.h"
#include "sys_module/models/Counter.h"
#include "sys_module/models/Signal.h"

namespace op {
using std::make_shared;

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
      datetime(env->sys_date),
      next_datetime(env->feeds[ticker]->next_ohlc->date) {
    _record_info(info);
    _check_all_conflict();
};

void SignalBase::_check_all_conflict() {

    _check_size();
    _check_conflict(takeprofit, takeprofit_pct, "takeprofit");
    _check_conflict(stoploss, stoploss_pct, "stoploss");
    _check_conflict(trailingstop, trailingstop_pct, "trailingstop");
};

void SignalBase::_check_size() {
    if (size < 0)
        throw std::logic_error("size should be Positive");
};

void SignalBase::_check_conflict(const double obj,
                                 const double obj_pct,
                                 const string &name) {
    if (obj != 0 && obj_pct != 0)
        throw except::OrderConflictError(); //TODO

    if (obj_pct != 0 && (obj_pct <= -1 || obj_pct >= 1))
        throw except::PctRangeError(); //TODO

    if (name != "price") {
        if (obj < 0)
            throw std::logic_error("{name.upper()} should be Positive");
        else if (obj_pct < 0)
            throw std::logic_error("{name.upper()} should be Positive");
    }
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
      signal_id(Counter::update_signal_id()) {
    _save_signals();
};

void Signal::_save_signals() {
    env->signals_normal_cur.push_back(make_shared<Signal>(*this));
}

SignalForPending::SignalForPending(
    const map<string, double> &info,
    const string &ticker,
    const string &strategy_name,
    const ActionType &action_type)

    : SignalBase(info, ticker, strategy_name, action_type),
      signal_id(Counter::update_signal_id()) {
    _save_signals();
};

void SignalForPending::_save_signals() {
    env->signals_pending_cur.push_back(make_shared<SignalForPending>(*this));
}

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
      signal_id(Counter::update_signal_by_trigger_id()) {
    _save_signals();
};

void SignalByTrigger::_save_signals() {
    env->signals_trigger_cur.push_back(make_shared<SignalByTrigger>(*this));
}

} // namespace op
