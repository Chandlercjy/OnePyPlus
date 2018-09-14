#include "DataType.h"
#include "OP_DECLARE.h"

#pragma once

OP_NAMESPACE_START

enum class ActionType;
class OrderGenerator;
class MarketOrder;
class Environment;
class SubmitOrderChecker;

class BrokerBase {
  public:
    BrokerBase();
    virtual ~BrokerBase() = default;

    Environment *env;

    void run();
    shared_ptr<SubmitOrderChecker> checker;

  protected:
    double _required_cash_func(const MarketOrderPtr &order);

    virtual Cash_func_ptr_type cash_func() = 0;

  private:
    shared_ptr<OrderGenerator> _order_generator;
    void _clear_submitted_order();
    void _generate_order();
    void _check_order();
    void _submit_order();
    const string _judge_long_or_short(const ActionType &action_type);
    void _process_cancel_tst_order();
    void _process_cancel_pending_order();
};

OP_NAMESPACE_END
