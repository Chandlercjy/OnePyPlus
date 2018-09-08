#include "DataType.h"
#include "OP_DECLARE.h"

#pragma once

OP_NAMESPACE_START

class Environment;

class SignalChecker {
  public:
    SignalChecker();
    Environment *env;

    void save_signals(const SignalPtr &value);
    void save_signals(const SignalForPendingPtr &value);
    void save_signals(const SignalByTriggerPtr &value);
    void save_signals(const SignalCancelTSTPtr &value);
    void save_signals(const SignalCancelPendingPtr &value);

    void check(const SignalBasePtr &signal);
    void check(const SignalCancelTSTPtr &signal);
    void check(const SignalCancelPendingPtr &signal);

  private:
    void _check_conflict(const double obj,
                         const double obj_pct,
                         const string &name);
    void _check_size(const int size);
};

OP_NAMESPACE_END
