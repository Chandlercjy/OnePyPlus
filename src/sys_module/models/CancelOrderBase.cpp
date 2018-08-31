#include "sys_module/models/BarBase.h"
#include "sys_module/models/CancelOrderBase.h"

namespace op {
class Environment;

template <typename T>
CancelOrderBase::CancelOrderBase(const shared_ptr<T> &signal)
    : env(Environment::get_instance()),
      strategy_name(signal->strategy_name),
      ticker(signal->ticker),
      trading_date(signal->datetime),
      long_or_short(signal->long_or_short),
      order_id(_counter++) {
    set_status(OrderStatus::Created);
    set_first_cur_price_and_signal_type(signal);
};

template <typename T>
inline void CancelOrderBase::set_first_cur_price_and_signal_type(const shared_ptr<T> &signal) {
    _first_cur_price = env->feeds[ticker]->execute_price();
};

inline void CancelOrderBase::set_status(const OrderStatus &value) {
    _status = value;
};

inline const OrderStatus CancelOrderBase::get_status() const {
    return _status;
};

} // namespace op

