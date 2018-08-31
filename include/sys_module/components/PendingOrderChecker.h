#pragma once

namespace op {
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

} // namespace op

