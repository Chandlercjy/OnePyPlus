#include "sys_module/models/BarBase.h"
#include "sys_module/models/CancelOrderBase.h"
#include "sys_module/models/Counter.h"
#include "sys_module/models/SignalCancel.h"

namespace op {
class Environment;

CancelOrderBase::CancelOrderBase(const shared_ptr<SignalCancelBase> &signal)
    : env(Environment::get_instance()),
      strategy_name(signal->strategy_name),
      ticker(signal->ticker),
      trading_date(signal->datetime),
      long_or_short(signal->long_or_short),
      order_id(Counter::update_order_id()) {
    set_status(OrderStatus::Created);
    set_first_cur_price_and_signal_type();
};

void CancelOrderBase::set_first_cur_price_and_signal_type() {
    _first_cur_price = env->feeds[ticker]->execute_price();
};

void CancelOrderBase::set_status(const OrderStatus &value) {
    _status = value;
};

inline const OrderStatus CancelOrderBase::get_status() const {
    return _status;
};

} // namespace op
