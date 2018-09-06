#include "OP_DECLARE.h"

#pragma once

OP_NAMESPACE_START

class PendingOrderBase;
class SignalChecker;

class TriggeredSignalGenerator {
  public:
    TriggeredSignalGenerator();
    void _generate_bare_signal(const shared_ptr<PendingOrderBase> &order);
    void _generate_full_signal(const shared_ptr<PendingOrderBase> &order);
    bool generate_triggered_signal(const shared_ptr<PendingOrderBase> &order);

  private:
    shared_ptr<SignalChecker> signal_checker;
};

OP_NAMESPACE_END
