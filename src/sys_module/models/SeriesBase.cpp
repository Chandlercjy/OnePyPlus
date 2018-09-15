#include "Constants.h"
#include "DataType.h"
#include "Environment.h"
#include "sys_module/models/BarBase.h"
#include "sys_module/models/SeriesBase.h"
#include "utils/utils.h"

OP_NAMESPACE_START

using namespace utils;

SeriesBase::SeriesBase()
    : env(Environment::get_instance()) { _initialize_data(); }

inline void SeriesBase::_initialize_data() {
    for (auto &ticker : env->tickers) {
        data[ticker + "_long"].push_back(SeriesStruct{env->fromdate, 0});
        data[ticker + "_short"].push_back(SeriesStruct{env->fromdate, 0});
    }
}

void SeriesBase::change_initial_value(const string &ticker,
                                      const double value,
                                      const string &long_or_short) {
    data[ticker + "_" + long_or_short][0].value = value;
};

double SeriesBase::latest(const string &ticker,
                          const string &long_or_short) {
    return data[ticker + "_" + long_or_short].back().value;
}

double SeriesBase::total_value() {
    double total = 0;
    for (auto &per_pair : data) {
        auto final_value = per_pair.second.back();
        total += final_value.value;
    }
    return total;
};

void SeriesBase::_append_value(const string &ticker,
                               const double value,
                               const string &long_or_short) {
    const string key = ticker + "_" + long_or_short;
    if (data[key].back().date == env->sys_date)
        data[key].back().value = value;
    else
        data[key].push_back(SeriesStruct{env->sys_date, value});
};
double SeriesBase::get_barly_cur_price(const string &ticker,
                                       const bool order_executed) {
    if (order_executed) {
        return env->feeds[ticker]->execute_price();
    } else {
        return env->feeds[ticker]->open();
    }
};

MoneySeries::MoneySeries(const string &name, const double initial_value)
    : env(Environment::get_instance()),
      _name(name) { _initialize_data(initial_value); };

const string MoneySeries::get_name() { return _name; };

void MoneySeries::change_initial_value(const double value) {
    data[0].value = value;
};

inline void MoneySeries::_initialize_data(const double initial_value) {
    data.push_back(SeriesStruct{env->fromdate, initial_value});
}

double MoneySeries::latest() {
    return data.back().value;
};

void MoneySeries::push_back(const SeriesStruct &value) {
    data.push_back(value);
};

void PositionSeries::update_order(const string &ticker,
                                  const double size,
                                  const ActionType &action_type,
                                  const double last_position,
                                  const string &long_or_short) {
    const double new_value = last_position + size * _direction(action_type);
    _append_value(ticker, new_value, long_or_short);
};

const int PositionSeries::_direction(const ActionType &action_type) {
    if (action_type == ActionType::Buy || action_type == ActionType::Short)
        return 1;
    return -1;
}

void AvgPriceSeries::update_order(const string &ticker,
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

    _append_value(ticker, new_value, long_or_short);
};

OP_NAMESPACE_END
