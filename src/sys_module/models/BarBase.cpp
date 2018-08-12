#include "../../DataType.h"
#include "../../Environment.h"
#include "BarBase.h"

namespace sys {

BarBase::BarBase(OhlcVector bar_series)
    : env(Environment::getInstance()),
      _bar_series(bar_series) {
    cur_bar = _bar_series.cbegin();
};

void BarBase::_update_iter_data() {
}

void BarBase::next() {
    if (is_suspended()) {

    } else
        next_directly();
}

void BarBase::next_directly() {
    ++previous_bar;
    ++cur_bar;
    ++next_bar;
    if (next_bar == _bar_series.cend())
        throw std::runtime_error("指针过头了");

    date = &(cur_bar)->date;
    open = &(cur_bar)->open;
    high = &(cur_bar)->high;
    low = &(cur_bar)->low;
    close = &(cur_bar)->close;
    volume = &(cur_bar)->volume;
}

void BarBase::initialize() {
}
bool BarBase::is_suspended() { return false; };

void BarBase::move_next_ohlc_to_cur_ohlc() {
}
void BarBase::_delete_ohlc() {
}
} // namespace sys
