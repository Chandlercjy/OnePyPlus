#include "Environment.h"
#include "sys_module/models/Counter.h"
#include "sys_module/models/SignalCancel.h"

OP_NAMESPACE_START
using std::make_shared;

SignalCancelBase::SignalCancelBase(
    const string &strategy_name,
    const string &ticker,
    const string &long_or_short)
    : env(Environment::get_instance()),
      strategy_name(strategy_name),
      ticker(ticker),
      long_or_short(long_or_short),
      datetime(env->sys_date),
      signal_id(Counter::update_signal_cancel_id()){};

SignalCancelTST::SignalCancelTST(
    const string &strategy_name,
    const string &ticker,
    const string &long_or_short,
    const bool takeprofit,
    const bool stoploss,
    const bool trailingstop)
    : SignalCancelBase(strategy_name, ticker, long_or_short),
      takeprofit(takeprofit),
      stoploss(stoploss),
      trailingstop(trailingstop) { _save_signals(); };

SignalCancelPending::SignalCancelPending(
    const string &strategy_name,
    const string &ticker,
    const string &long_or_short,
    const double below_price,
    const double above_price)
    : SignalCancelBase(strategy_name, ticker, long_or_short),
      below_price(below_price),
      above_price(above_price) { _save_signals(); };

void SignalCancelTST::_check_conflict(){};
void SignalCancelPending::_check_conflict(){};

void SignalCancelTST::_save_signals() {
    env->signals_cancel_tst_cur.push_back(make_shared<SignalCancelTST>(*this));
}

void SignalCancelPending::_save_signals() {
    env->signals_cancel_pending_cur.push_back(make_shared<SignalCancelPending>(*this));
}

OP_NAMESPACE_END

