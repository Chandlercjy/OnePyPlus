#include "../../DataType.h"
#include "../../Environment.h"
#include "SeriesBase.h"

namespace sys {

SeriesBase::SeriesBase()
    : env(Environment::get_instance()) { _initialize_data(); }

inline void SeriesBase::_initialize_data() {
    for (auto &ticker : env->tickers) {
        _data[ticker + "_long"].push_back(SeriesStruct{env->fromdate, 0});
        _data[ticker + "_short"].push_back(SeriesStruct{env->fromdate, 0});
    }
}

void SeriesBase::change_initial_value(const string &ticker,
                                      const double value,
                                      const string &long_or_short) {
    _data[ticker + "_" + long_or_short][0].value = value;
};

double SeriesBase::latest(const string &ticker,
                          const string &long_or_short,
                          const int value) const {};

double SeriesBase::total_value() const {};

void SeriesBase::_append_value(const string &ticker,
                               const double value,
                               const string &long_or_short){};
double SeriesBase::get_barly_cur_price(const string &ticker,
                                       const bool order_executed){};

} // namespace sys
