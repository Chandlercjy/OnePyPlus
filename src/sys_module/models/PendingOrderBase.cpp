#include "Environment.h"
#include "sys_module/models/BarBase.h"
#include "sys_module/models/Counter.h"
#include "sys_module/models/PendingOrderBase.h"
#include "sys_module/models/Signal.h"

OP_NAMESPACE_START

PendingOrderBase::PendingOrderBase(const ActionType &action_type,
                                   const OrderType &order_type,
                                   const shared_ptr<SignalBase> &signal,
                                   const int mkt_id,
                                   const string &trigger_key)
    : env(Environment::get_instance()),
      strategy_name(signal->strategy_name),
      ticker(signal->ticker),
      size(signal->size()),
      trading_date(signal->datetime),
      order_id(Counter::update_order_id()),
      mkt_id(mkt_id),
      signal_info(signal->info),
      trigger_key(trigger_key),
      action_type(action_type),
      order_type(order_type),
      target_below(set_target_below(action_type, order_type)),
      _signal_type("normal"),
      _cur_price_when_generated(env->feeds[ticker]->execute_price()){};

PendingOrderBase::PendingOrderBase(const ActionType &action_type,
                                   const OrderType &order_type,
                                   const SignalByTriggerPtr &signal,
                                   const int mkt_id,
                                   const string &trigger_key)
    : env(Environment::get_instance()),
      strategy_name(signal->strategy_name),
      ticker(signal->ticker),
      size(signal->size()),
      trading_date(signal->datetime),
      order_id(Counter::update_order_id()),
      mkt_id(mkt_id),
      signal_info(signal->info),
      trigger_key(trigger_key),
      action_type(action_type),
      order_type(order_type),
      target_below(set_target_below(action_type, order_type)),
      _signal_type("triggered"),
      _cur_price_when_generated(signal->execute_price){};

const double PendingOrderBase::cur_open() const {
    return env->feeds[ticker]->open();
};
const double PendingOrderBase::cur_high() const {
    return env->feeds[ticker]->high();
};

const double PendingOrderBase::cur_low() const {
    return env->feeds[ticker]->low();
};

const double PendingOrderBase::difference() {
    if (trigger_key.find("pct") == string::npos)
        return signal_info[trigger_key] / size;
    return signal_info[trigger_key] * _cur_price_when_generated;
};

const double PendingOrderBase::cur_high_cross_target_price() {
    return target_price() < cur_high() ? true : false;
};
const double PendingOrderBase::cur_low_cross_target_price() {
    return target_price() > cur_low() ? true : false;
};
const bool PendingOrderBase::is_with_mkt() {
    return trigger_key == "price" ? false : true; //判断是否是跟随市价单的挂单
};
const double PendingOrderBase::below_price(const double diff) {
    return _cur_price_when_generated - diff;
};
const double PendingOrderBase::above_price(const double diff) {
    return _cur_price_when_generated + diff;
};

const double PendingOrderBase::target_price() {
    if (trigger_key == "price")
        return signal_info[trigger_key];
    else if (target_below)
        below_price(difference());
    return above_price(difference());
};

const bool PendingOrderBase::is_triggered() {
    if (target_below)
        return cur_low_cross_target_price();
    return cur_high_cross_target_price();
};

void PendingOrderBase::set_status(const OrderStatus &value) {
    _status = value;
};

const OrderStatus PendingOrderBase::get_status() const {
    return _status;
};

const double PendingOrderBase::get_cur_price_when_generated() const {
    return _cur_price_when_generated;
};

const string PendingOrderBase::get_signal_type() const {
    return _signal_type;
};

const bool PendingOrderBase::set_target_below(const ActionType &action_type,
                                              const OrderType &order_type) {
    switch (action_type) {
        case ActionType::Buy:
            switch (order_type) {
                case OrderType::Limit:
                    break;
                case OrderType::Stop:
                    return false;
                case OrderType::Trailing_stop:
                    return false;
                case OrderType::Market:
                    throw std::logic_error("Never raised");
                    break;
            }
            break;
        case ActionType::Sell:
            switch (order_type) {
                case OrderType::Limit:
                    return false;
                case OrderType::Stop:
                    break;
                case OrderType::Trailing_stop:
                    break;
                case OrderType::Market:
                    throw std::logic_error("Never raised");
                    break;
            }
            break;
        case ActionType::Short:
            switch (order_type) {
                case OrderType::Limit:
                    return false;
                case OrderType::Stop:
                    break;
                case OrderType::Trailing_stop:
                    break;
                case OrderType::Market:
                    throw std::logic_error("Never raised");
                    break;
            }
            break;
        case ActionType::Cover:
            switch (order_type) {
                case OrderType::Limit:
                    break;
                case OrderType::Stop:
                    return false;
                case OrderType::Trailing_stop:
                    return false;
                case OrderType::Market:
                    throw std::logic_error("Never raised");
                    break;
            }
            break;
        case ActionType::Cancel:
            throw std::logic_error("Never raised");
            break;
    }
    return true;
}

OP_NAMESPACE_END
