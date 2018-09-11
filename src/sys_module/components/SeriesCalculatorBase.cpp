#include "Environment.h"
#include "SeriesCalculatorBase.h"
#include "utils/utils.h"

OP_NAMESPACE_START
using namespace utils;

SeriesCalculatorBase::SeriesCalculatorBase()
    : env(Environment::get_instance()){};

void SeriesCalculatorBase::_append_value(SeriesDict &series,
                                         const string &ticker,
                                         const double value,
                                         const string &long_or_short) {
    const string key = ticker + "_" + long_or_short;
    if (series[key].back().date == env->sys_date)
        series[key].back().value = Math::Round(value, 2);
    else
        series[key].emplace_back(SeriesStruct{env->sys_date, value});
};

const int SeriesCalculatorBase::_direction(const ActionType &action_type) {
    if (action_type == ActionType::Buy || action_type == ActionType::Short)
        return 1;
    else
        return -1;
}

void SeriesCalculatorBase::initialize_series(SeriesDict &series) {
    for (auto &ticker : env->tickers) {
        series[ticker + "_long"].emplace_back(SeriesStruct{env->fromdate, 0});
        series[ticker + "_short"].emplace_back(SeriesStruct{env->fromdate, 0});
    }
}

void SeriesCalculatorBase::change_initial_value(SeriesDict &series,
                                                const string &ticker,
                                                const double value,
                                                const string &long_or_short) {
    series[ticker + "_" + long_or_short].front().value = value;
};

double SeriesCalculatorBase::get_total_value(SeriesDict &series) {
    double total = 0;
    for (auto &per_pair : series) {
        auto final_value = per_pair.second.back();
        total += final_value.value;
    }
    return total;
};

void SeriesCalculatorBase::update_position(SeriesDict &series,
                                           const string &ticker,
                                           const double size,
                                           const ActionType &action_type,
                                           const double last_position,
                                           const string &long_or_short) {
    const double new_value = last_position + size * _direction(action_type);
    _append_value(series, ticker, new_value, long_or_short);
}

void SeriesCalculatorBase::update_avg_price(SeriesDict &series,
                                            const string &ticker,
                                            const double size,
                                            const double execute_price,
                                            const double last_position,
                                            const double last_avg_price,
                                            const double new_position,
                                            const string &long_or_short) {
    double new_value = 0;
    if (new_position == 0) {
    } else if (new_position > last_position) {
        new_value = (last_position * last_avg_price + size * execute_price) /
                    new_position;
    } else {
        new_value = last_avg_price;
    };

    _append_value(series, ticker, new_value, long_or_short);
}

void SeriesCalculatorBase::update_money(SeriesVector &series,
                                        const string &trading_date,
                                        const double value) {
    series.emplace_back(SeriesStruct{trading_date, value});
}

static double get_latest(SeriesDict &series,
                         const string &ticker,
                         const string &long_or_short) {
    return series[ticker + "_" + long_or_short].back().value;
}

OP_NAMESPACE_END
