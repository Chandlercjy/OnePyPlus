#include "Environment.h"
#include "sys_module/models/BarBase.h"
#include "sys_module/models/TrailingOrderBase.h"

namespace op {

template <typename T>
TrailingOrderBase::TrailingOrderBase(const T &signal,
                                     const int mkt_id,
                                     const string &trigger_key)
    : PendingOrderBase(signal, mkt_id, trigger_key) {
    _initialize_latest_target_price();
};

const double TrailingOrderBase::target_price() {
    if (env->instrument == "A_shares") {
        if (target_below() && cur_open() < _latest_target_price)
            return cur_open();
        else if ((!target_below()) && cur_open() > _latest_target_price)
            return cur_open();
    };
    return _latest_target_price;
};

const bool TrailingOrderBase::is_triggered() {

    if (target_below()) {
        if (cur_low_cross_target_price()) {
            return true;
        } else {
            double new_value;
            if (get_action_type() == ActionType::Sell)
                new_value = cur_open() - difference();
            else
                new_value = cur_high() - difference();
            if (_latest_target_price < new_value)
                _latest_target_price = new_value;
            return false;
        }
    } else {
        if (cur_high_cross_target_price()) {
            return true;
        } else {
            double new_value;
            if (get_action_type() == ActionType::Sell)
                new_value = cur_low() + difference();
            else
                new_value = cur_open() + difference();
            if (_latest_target_price > new_value)
                _latest_target_price = new_value;
            return false;
        }
    }
};

void TrailingOrderBase::_initialize_latest_target_price() {
    if (target_below())
        _latest_target_price = _first_cur_price - difference();
    else
        _latest_target_price = _first_cur_price + difference();
};

const double TrailingOrderBase::cur_high_cross_target_price() {
    return _latest_target_price < cur_high() ? true : false;
};

const double TrailingOrderBase::cur_low_cross_target_price() {
    return _latest_target_price > cur_low() ? true : false;
};
} // namespace op

