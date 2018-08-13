#include "../../DataType.h"
#include "../../Environment.h"
#include "BarBase.h"

namespace sys {

BarBase::BarBase(const string &ticker, const string &frequency)
    : env(Environment::getInstance()),
      ticker(ticker),
      frequency(frequency) {}

const string BarBase::date() {
    return cur_bar->date;
}

const double BarBase::open() {
    return cur_bar->open;
}

const double BarBase::high() {
    return cur_bar->high;
}

const double BarBase::low() {
    return cur_bar->low;
}

const double BarBase::close() {
    return cur_bar->close;
}

const double BarBase::volume() {
    return cur_bar->volume;
}

const double BarBase::execute_price() {
    if (env->execute_on_close_or_next_open == "open")
        return next_bar->open;
    return cur_bar->close;
}

const double BarBase::cur_price() {
    return cur_bar->close;
}

void BarBase::initialize() {
}

void BarBase::_update_iter_data() {
}

void BarBase::next() {
    if (is_suspended()) {
        env->cur_suspended_tickers->push_back(ticker);

    } else
        next_directly();
}

void BarBase::next_directly() {
    ++previous_bar;
    ++cur_bar;
    ++next_bar;
    if (next_bar == _iter_data->cend())
        throw std::runtime_error("指针过头了");
}

bool BarBase::is_suspended() { return false; }

void BarBase::move_next_ohlc_to_cur_ohlc() {
}
void BarBase::_delete_ohlc() {
}
} // namespace sys
