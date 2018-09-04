#include "OP_DECLARE.h"

#pragma once

OP_NAMESPACE_START

class PendingOrderBase;

class TriggeredSignalGenerator {
  public:
    TriggeredSignalGenerator() = delete;

    static void _generate_bare_signal(const shared_ptr<PendingOrderBase> &order);

    static void _generate_full_signal(const shared_ptr<PendingOrderBase> &order);

    static bool generate_triggered_signal(const shared_ptr<PendingOrderBase> &order);
};

OP_NAMESPACE_END

