#include "DataType.h"
#include "OP_DECLARE.h"
#include "OrderBase.h"

#pragma once

OP_NAMESPACE_START

class SignalBase;

class PendingOrderBase {
  public:
    PendingOrderBase(const ActionType &action_type,
                     const OrderType &order_type,
                     const shared_ptr<SignalBase> &signal,
                     const int mkt_id,
                     const string &trigger_key);
    PendingOrderBase(const ActionType &action_type,
                     const OrderType &order_type,
                     const SignalByTriggerPtr &signal,
                     const int mkt_id,
                     const string &trigger_key);

    Environment *env;

    const string strategy_name;
    const string ticker;
    double size;
    const string trading_date;

    const int order_id;
    const int mkt_id;

    map<string, double> signal_info;

    virtual void set_status(const OrderStatus &value);

    const string trigger_key;
    virtual const bool is_triggered();
    const bool is_with_mkt();
    virtual const double target_price();
    const double difference();

    const OrderStatus get_status() const;
    const double get_cur_price_when_generated() const;
    const string get_signal_type() const;

    const ActionType action_type;
    const OrderType order_type;
    const bool target_below;

  protected:
    OrderStatus _status;

    const string _signal_type;
    const double _cur_price_when_generated;

    const double cur_open() const;
    const double cur_high() const;
    const double cur_low() const;
    virtual const double cur_high_cross_target_price();
    virtual const double cur_low_cross_target_price();
    const double below_price(const double diff);
    const double above_price(const double diff);

    static const bool set_target_below(const ActionType &action_type,
                                       const OrderType &order_type);
};

OP_NAMESPACE_END
