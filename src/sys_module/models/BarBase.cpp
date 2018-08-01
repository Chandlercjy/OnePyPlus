#include "BarBase.h"

BarBase::BarBase(OhlcVector bar_series)
    : cur_bar(bar_series.begin()),
      _bar_series(bar_series){};

void BarBase::_set_ohlc() {
    this->date = &(this->cur_bar)->date;
    this->open = &(this->cur_bar)->open;
    this->high = &(this->cur_bar)->high;
    this->low = &(this->cur_bar)->low;
    this->close = &(this->cur_bar)->close;
    this->volume = &(this->cur_bar)->volume;
}

void BarBase::next() {
    ++(this->cur_bar);
    ++_bar_count;
    if (_bar_count > _total_size)
        throw std::runtime_error("指针过头了");

    _set_ohlc();
}
