#include "../DataType.h"
#include <functional>

#pragma once

namespace sys {

using std::shared_ptr;
using std::unique_ptr;

class OrderGenerator;
class MarketOrder;
class Environment;
class SubmitOrderChecker;

class BrokerBase {
  public:
    BrokerBase();
    Environment *env;

    void run();

  protected:
    template <typename broker_name>
    void save_to_env(const broker_name *self_ptr);
    double _required_cash_func(const shared_ptr<MarketOrder> &order);

    virtual Cash_func_ptr_type cash_func() = 0;
    shared_ptr<SubmitOrderChecker> _checker;

  private:
    shared_ptr<OrderGenerator> _order_generator;
    void _clear_submitted_order();
    void _generate_order();
    void _check_order();
    void _submit_order();
    void _judge_long_or_short();
    void _process_cancel_order();
};
} // namespace sys
