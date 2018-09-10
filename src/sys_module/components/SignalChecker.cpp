#include "Environment.h"
#include "Exceptions.h"
#include "sys_module/components/SignalChecker.h"
#include "sys_module/models/Signal.h"
#include "sys_module/models/SignalCancel.h"

OP_NAMESPACE_START

SignalChecker::SignalChecker()
    : env(Environment::get_instance()){};

void SignalChecker::_check_conflict(const double obj,
                                    const double obj_pct,
                                    const string &name) {
    if (obj != 0 && obj_pct != 0)
        throw OrderConflictError(); //TODO

    if (obj_pct != 0 && (obj_pct <= -1 || obj_pct >= 1))
        throw PctRangeError(); //TODO

    if (name != "price") {
        if (obj < 0)
            throw std::logic_error("{name.upper()} should be Positive");
        else if (obj_pct < 0)
            throw std::logic_error("{name.upper()} should be Positive");
    }
};

void SignalChecker::_check_size(const int size) {
    if (size < 0)
        throw std::logic_error("size should be Positive");
};

void SignalChecker::check(const SignalBasePtr &signal) {
    _check_size(signal->size());
    _check_conflict(signal->takeprofit(), signal->takeprofit_pct(), "takeprofit");
    _check_conflict(signal->stoploss(), signal->stoploss_pct(), "stoploss");
    _check_conflict(signal->trailingstop(), signal->trailingstop_pct(), "trailingstop");
};

void SignalChecker::check(const SignalCancelTSTPtr &signal){};

void SignalChecker::check(const SignalCancelPendingPtr &signal) {
    if (signal->below_price == 0 && signal->above_price == 0)
        throw std::logic_error("Should set one of below price & above price ");
    else if (signal->below_price != 0 && signal->above_price != 0)
        throw std::logic_error("Below price & above price can't be set together");
};

void SignalChecker::save_signals(const SignalPtr &value) {
    env->signals_normal_cur.push_back(value);
};
void SignalChecker::save_signals(const SignalForPendingPtr &value) {
    env->signals_pending_cur.push_back(value);
};

void SignalChecker::save_signals(const SignalByTriggerPtr &value) {
    env->signals_trigger_cur.push_back(value);
};

void SignalChecker::save_signals(const SignalCancelTSTPtr &value) {
    env->signals_cancel_tst_cur.push_back(value);
};

void SignalChecker::save_signals(const SignalCancelPendingPtr &value) {
    env->signals_cancel_pending_cur.push_back(value);
};

OP_NAMESPACE_END
