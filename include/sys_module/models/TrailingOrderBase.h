#include "OP_DECLARE.h"
#include "PendingOrderBase.h"

#pragma once

OP_NAMESPACE_START

class TrailingOrderBase : public PendingOrderBase {
  public:
    TrailingOrderBase(const shared_ptr<SignalBase> &signal,
                      const int mkt_id,
                      const string &trigger_key);
    virtual const ActionType get_action_type() const override = 0;
    virtual const OrderType get_order_type() const override = 0;
    virtual const bool target_below() const override = 0;
    const double cur_high_cross_target_price() override;
    const double cur_low_cross_target_price() override;

    const double target_price() override;
    const bool is_triggered() override;

  private:
    double _latest_target_price;
    void _initialize_latest_target_price();
};

OP_NAMESPACE_END
