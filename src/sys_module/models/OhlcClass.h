#pragma once

#include <string>

using std::string;

struct OhlcStruct {
    OhlcStruct(const string date, const double open, const double high,
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
