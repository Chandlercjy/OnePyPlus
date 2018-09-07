#include "OP_DECLARE.h"
#include "PendingOrder.h"

#pragma once

OP_NAMESPACE_START

class TrailingOrderBase : public PendingOrder {
  public:
    TrailingOrderBase(const ActionType &action_type,
                      const OrderType &order_type,
                      const shared_ptr<SignalBase> &signal,
                      const int mkt_id,
                      const string &trigger_key);
    TrailingOrderBase(const ActionType &action_type,
                      const OrderType &order_type,
                      const SignalByTriggerPtr &signal,
                      const int mkt_id,
                      const string &trigger_key);
    const double cur_high_cross_target_price() override;
    const double cur_low_cross_target_price() override;

    const double target_price() override;
    const bool is_triggered() override;

  private:
    double _latest_target_price;
    void _initialize_latest_target_price();
};

OP_NAMESPACE_END
