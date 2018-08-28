#include "Signal.h"
#include <map>
#include <string>
#include <vector>

#pragma once

namespace sys {

enum class ActionType;
enum class OrderType;
enum class OrderStatus;
class SignalBase;
using std::map;
using std::shared_ptr;

class OrderBase {

  public:
    template <typename T>
    OrderBase(const shared_ptr<T> &signal,
              const int mkt_id);

    Environment *env;

    const string strategy_name;
    const string ticker;
    const double size;
    const string trading_date;

    const int order_id;
    const int mkt_id;

    map<string, double> signal_info;

    virtual const ActionType get_action_type() const = 0;
    virtual const OrderType get_order_type() const = 0;
    virtual void set_status(const OrderStatus &value);

    template <typename T>
    void set_first_cur_price_and_signal_type(const shared_ptr<T> &signal);

    const OrderStatus get_status() const;
    const double get_first_cur_price() const;
    const string get_signal_type() const;

  protected:
    static int _counter;
    OrderStatus _status;

    string _signal_type;
    double _first_cur_price;

    template <typename T>
    void _save_signal_info(const T &signal);
};

int OrderBase::_counter = 1;
} // namespace sys
