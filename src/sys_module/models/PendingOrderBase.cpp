#include "../../Environment.h"
#include "BarBase.h"
#include "PendingOrderBase.h"

namespace sys {

template <typename T>
PendingOrderBase::PendingOrderBase(const T &signal,
                                   const int mkt_id,
                                   const string &trigger_key)
    : OrderBase(signal, mkt_id),
      trigger_key(trigger_key){};

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
    return signal_info[trigger_key] * _first_cur_price;
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
const double PendingOrderBase::below_price(const double &diff) {
    return _first_cur_price - diff;
};
const double PendingOrderBase::above_price(const double &diff) {
    return _first_cur_price + diff;
};

const double PendingOrderBase::target_price() {
    if (trigger_key == "price")
        return signal_info[trigger_key];
    else if (target_below())
        below_price(difference());
    return above_price(difference());
};

const bool PendingOrderBase::is_triggered() {
    if (target_below())
        return cur_low_cross_target_price();
    return cur_high_cross_target_price();
};

} // namespace sys
