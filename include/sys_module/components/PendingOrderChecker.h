#include "OP_DECLARE.h"

#pragma once

OP_NAMESPACE_START

class Environment;

class PendingOrderChecker {
  public:
    PendingOrderChecker();
    Environment *env;

    void run();

  private:
    void _check_orders_pending();
    void _check_orders_pending_with_mkt();
};

OP_NAMESPACE_END
