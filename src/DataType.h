#pragma once

#include <map>
#include <string>

namespace sys {

using std::map;
using std::shared_ptr;
using std::string;
using std::vector;

struct OhlcStruct {
    OhlcStruct(const string &date, const double open, const double high,
               const double low, const double close, const double volume)
        : date(date),
          open(open),
          high(high),
          low(low),
          close(close),
          volume(volume){};

    const string date;
    const double open;
    const double high;
    const double low;
    const double close;
    const double volume;
};

struct SeriesStruct {
    SeriesStruct(const string &date, const double value)
        : date(date), value(value){};
    const string date;
    double value;
};

using OhlcVector = vector<OhlcStruct>;

template <typename value, typename key = string>
using ModuleMap = map<key, shared_ptr<value>>;

template <typename T>
using SignalBox = vector<shared_ptr<T>>;

template <typename T>
using OrderBox = vector<shared_ptr<T>>;

} // namespace sys
