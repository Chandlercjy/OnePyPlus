#include "OP_DECLARE.h"
#include "Constants.h"
#include "Environment.h"

#pragma once

OP_NAMESPACE_START

class SignalCancelBase;

class CancelOrderBase {
  public:
    explicit CancelOrderBase(const shared_ptr<SignalCancelBase> &signal);

    Environment *env;

    const string strategy_name;
    const string ticker;
    const string trading_date;
    const string long_or_short;

    const int order_id;

    map<string, double> signal_info;

    void set_first_cur_price_and_signal_type();

    void set_status(const OrderStatus &value);
    const ActionType get_action_type() const;
    const OrderStatus get_status() const;

    virtual const bool is_target(const string &trigger_key) = 0;
    virtual const bool is_target(const double target_price) = 0;

  protected:
    virtual void _save_signal_info() = 0;

  private:
    double _first_cur_price;
    OrderStatus _status;
};

OP_NAMESPACE_END

