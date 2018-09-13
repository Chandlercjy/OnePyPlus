#include "OP_DECLARE.h"
#include "Signal.h"

#pragma once

OP_NAMESPACE_START

enum class ActionType;
enum class OrderType;
enum class OrderStatus;
class Signal;
class SignalByTrigger;
using std::map;
using std::shared_ptr;

class OrderBase {

  public:
    OrderBase(const shared_ptr<Signal> &signal,
              const int mkt_id);

    OrderBase(const shared_ptr<SignalByTrigger> &signal,
              const int mkt_id);

    Environment *env;

    const string strategy_name;
    const string ticker;
    double size;
    const string trading_date;

    const int order_id;
    const int mkt_id;

    map<string, double> signal_info;

    virtual void set_status(const OrderStatus &value);

    void set_cur_price_when_generated_and_signal_type(const shared_ptr<SignalBase> &signal);
    //void set_cur_price_when_generated_and_signal_type_trigger(const shared_ptr<SignalBase> &signal);

    const OrderStatus get_status() const;
    const double get_cur_price_when_generated() const;
    const string get_signal_type() const;
    string from_signal_type;
    OrderType from_order_type;

  protected:
    OrderStatus _status;

    double _cur_price_when_generated;
};

OP_NAMESPACE_END
