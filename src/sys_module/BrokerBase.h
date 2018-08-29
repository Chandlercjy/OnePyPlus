#include <functional>

#pragma once

namespace sys {

using std::shared_ptr;

class OrderGenerator;
class MarketOrder;
class Environment;

class BrokerBase {
  public:
    BrokerBase();
    Environment *env;

    void run();

  protected:
    template <typename broker_name>
    void save_to_env(const broker_name *self_ptr);
    virtual const double _required_cash_func(const shared_ptr<MarketOrder> &order) = 0;

  private:
    //make_shared _checker(); //TODO：返回SubmitOrderChencker
    const shared_ptr<OrderGenerator> _order_generator;
    void _clear_submitted_order();
    void _generate_order();
    void _check_order();
    void _submit_order();
    void _judge_long_or_short();
    void _process_cancel_order();
};
} // namespace sys
