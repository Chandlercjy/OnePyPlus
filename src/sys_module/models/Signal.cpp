#include "../../Environment.h"
#include "../../Exceptions.h"
#include "BarBase.h"
#include "Signal.h"

namespace sys {
using std::make_shared;

SignalBase::SignalBase(
    const string &strategy_name,
    const ActionType &action_type,
    const double size,
    const string &ticker,
    const double price,
    const double takeprofit,
    const double takeprofit_pct,
    const double stoploss,
    const double stoploss_pct,
    const double trailingstop,
    const double trailingstop_pct)
    : env(Environment::get_instance()),
      strategy_name(strategy_name),
      action_type(action_type),
      size(size),
      ticker(ticker),
      price(price),
      takeprofit(takeprofit),
      takeprofit_pct(takeprofit_pct),
      stoploss(stoploss),
      stoploss_pct(stoploss_pct),
      trailingstop(trailingstop),
      trailingstop_pct(trailingstop_pct),
      signal_id(_counter++),
      datetime(env->sys_date),
      next_datetime(env->feeds[ticker]->next_ohlc->date) {
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

Signal::Signal(
    const string &strategy_name,
    const ActionType &action_type,
    const double size,
    const string &ticker,
    const double price,
    const double takeprofit,
    const double takeprofit_pct,
    const double stoploss,
    const double stoploss_pct,
    const double trailingstop,
    const double trailingstop_pct)

    : SignalBase(strategy_name, action_type, size,
                 ticker, price, takeprofit, takeprofit_pct,
                 stoploss, stoploss_pct, trailingstop,
                 trailingstop_pct) {

    _save_signals();
};

void Signal::_save_signals() {
    env->signals_normal_cur.push_back(make_shared<Signal>(*this));
}

SignalForPending::SignalForPending(
    const string &strategy_name,
    const ActionType &action_type,
    const double size,
    const string &ticker,
    const double price,
    const double takeprofit,
    const double takeprofit_pct,
    const double stoploss,
    const double stoploss_pct,
    const double trailingstop,
    const double trailingstop_pct)

    : SignalBase(strategy_name, action_type, size,
                 ticker, price, takeprofit, takeprofit_pct,
                 stoploss, stoploss_pct, trailingstop,
                 trailingstop_pct) {

    _save_signals();
};

void SignalForPending::_save_signals() {
    env->signals_pending_cur.push_back(make_shared<SignalForPending>(*this));
}

SignalByTrigger::SignalByTrigger(
    const OrderType &order_type,
    const int mkt_id,
    const string &trigger_key,
    const double execute_price,
    const double first_cur_price,
    const shared_ptr<OrderBase> &parent_order,
    const string &strategy_name,
    const ActionType &action_type,
    const double size,
    const string &ticker,
    const double price,
    const double takeprofit,
    const double takeprofit_pct,
    const double stoploss,
    const double stoploss_pct,
    const double trailingstop,
    const double trailingstop_pct)

    : SignalBase(strategy_name, action_type, size,
                 ticker, price, takeprofit, takeprofit_pct,
                 stoploss, stoploss_pct, trailingstop,
                 trailingstop_pct),
      order_type(order_type),
      mkt_id(mkt_id),
      trigger_key(trigger_key),
      execute_price(execute_price),
      first_cur_price(first_cur_price),
      parent_order(parent_order),
      signal_id(_counter++) {
    _save_signals();
};

void SignalByTrigger::_save_signals() {
    env->signals_trigger_cur.push_back(make_shared<SignalByTrigger>(*this));
}

} // namespace sys
