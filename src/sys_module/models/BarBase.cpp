#include "DataType.h"
#include "Environment.h"
#include "sys_module/ReaderBase.h"
#include "sys_module/models/BarBase.h"
#include "utils/arrow.h"
#include "utils/easy_func.h"
#include "utils/utils.h"

OP_NAMESPACE_START
using namespace utils;

BarBase::BarBase(const string &ticker, const string &frequency)
    : env(Environment::get_instance()),
      ticker(ticker),
      frequency(frequency) {}

const string BarBase::date() const { return current_ohlc->date; }
const double BarBase::open() const { return current_ohlc->open; }
const double BarBase::high() const { return current_ohlc->high; }
const double BarBase::low() const { return current_ohlc->low; }
const double BarBase::close() const { return current_ohlc->close; }
const double BarBase::volume() const { return current_ohlc->volume; }
const double BarBase::cur_price() const { return current_ohlc->close; }
const string BarBase::next_date() const {
    if (is_bar_series_end())
        return current_ohlc->date;
    return next_ohlc->date;
}

const double BarBase::execute_price() const {
    if (env->execute_on_close_or_next_open == "open") {
        if (is_bar_series_end())
            return current_ohlc->close;
        return next_ohlc->open;
    }
    return current_ohlc->close;
}

bool BarBase::initialize(int buffer_day) {
    string sys_date = env->sys_date;
    string start = arrow::shift_days_to_str(env->fromdate, -buffer_day);
    string end = env->todate;

    if (buffer_day > 500) {
        _delete_ohlc("Delete OHLC for PRE_OHLC");
        return false;
    };

    if (_bar_series == nullptr) {
        _update_iter_data(start, end);
        if (next_ohlc == _bar_series->cend()) {
            _delete_ohlc("Delete OHLC for ALL");
            return false;
        };
    };

    while (next_ohlc != _bar_series->cend() &&
           arrow::is_lte(next_ohlc->date, sys_date)) {
        next_directly();
        if (previous_ohlc == _bar_series->cend() ||
            current_ohlc == _bar_series->cend() ||
            next_ohlc == _bar_series->cend()) {
            _delete_ohlc("Delete OHLC for SOME");
            return false;
        };
    };

    if (previous_ohlc != _bar_series->cend() &&
        arrow::is_gte(previous_ohlc->date, sys_date)) {
        buffer_day += 300;
        _bar_series = nullptr;
        return initialize(buffer_day);
    }

    return true;
}; // namespace op

void BarBase::_update_iter_data(const string &start, const string &end) {
    auto reader = env->readers[ticker];
    if (!reader) {
        utils::Log::handle_error(__FILE__, __LINE__, "No ticker in readers!");
    }
    _bar_series = reader->load(start, end, frequency);
    if (_bar_series->empty()) {
        utils::Log::handle_error(__FILE__, __LINE__, "Load no data in readers!");
    }
    previous_ohlc = _bar_series->cbegin();
    current_ohlc = ++_bar_series->cbegin();
    next_ohlc = ++++_bar_series->cbegin();
}

void BarBase::next() {
    if (is_suspended()) {
        env->cur_suspended_tickers.push_back(ticker);
        env->suspended_tickers_record[ticker].push_back(ticker);
    } else
        next_directly();
}

void BarBase::next_directly() {
    ++previous_ohlc;
    ++current_ohlc;
    ++next_ohlc;
}

bool BarBase::is_suspended() {
    const string now = env->sys_date;
    const string tomorrow = next_ohlc->date;
    if (arrow::is_lte(tomorrow, now))
        return false;
    return true;
}

void BarBase::_delete_ohlc(const string &msg) {
    env->readers.erase(ticker);
    std::cout << " Delete " << ticker << " for lack of " << msg << std::endl; //TODO: 添加Logger
    env->cur_suspended_tickers.push_back(ticker);
    env->suspended_tickers_record[ticker].push_back(ticker);
}

bool BarBase::is_bar_series_end() const {
    return next_ohlc == _bar_series->cend() ? true : false;
};

OP_NAMESPACE_END
