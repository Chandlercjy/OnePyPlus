#include "../../Constants.h"
#include "../../Environment.h"
#include <string>

#pragma once

namespace op {
using std::string;

class CancelOrderBase {
  public:
    template <typename T>
    explicit CancelOrderBase(const shared_ptr<T> &signal);

    Environment *env;

    const string strategy_name;
    const string ticker;
    const string trading_date;
    const string long_or_short;

    const int order_id;

    map<string, double> signal_info;

    template <typename T>
    void set_first_cur_price_and_signal_type(const shared_ptr<T> &signal);

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

} // namespace op
