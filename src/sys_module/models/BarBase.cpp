#include "BarBase.h"

namespace sys {

BarBase::BarBase(OhlcVector bar_series)
    : _bar_series(bar_series) { cur_bar = _bar_series.cbegin(); };

void BarBase::_set_ohlc() {
    date = &(cur_bar)->date;
    open = &(cur_bar)->open;
    high = &(cur_bar)->high;
    low = &(cur_bar)->low;
    close = &(cur_bar)->close;
    volume = &(cur_bar)->volume;
}

void BarBase::next() {
    ++(cur_bar);
    if (cur_bar == _bar_series.cend())
        throw std::runtime_error("指针过头了");

    _set_ohlc();
}
} // namespace sys
