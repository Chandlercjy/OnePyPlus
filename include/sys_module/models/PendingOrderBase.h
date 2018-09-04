#include "OP_DECLARE.h"
#include "OrderBase.h"

#pragma once

OP_NAMESPACE_START

class SignalBase;

class PendingOrderBase : public OrderBase {
  public:
    PendingOrderBase(const shared_ptr<SignalBase> &signal,
                     const int mkt_id,
                     const string &trigger_key);
    virtual const ActionType get_action_type() const override = 0;
    virtual const OrderType get_order_type() const override = 0;
    virtual const bool target_below() const = 0;

    const string trigger_key;
    virtual const bool is_triggered();
    const bool is_with_mkt();
    virtual const double target_price();
    const double difference();

  protected:
    const double cur_open() const;
    const double cur_high() const;
    const double cur_low() const;
    virtual const double cur_high_cross_target_price();
    virtual const double cur_low_cross_target_price();
    const double below_price(const double diff);
    const double above_price(const double diff);
};

OP_NAMESPACE_END
