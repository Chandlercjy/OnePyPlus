#pragma once

#include "../../TypeDef.h"
#include <string>
#include <vector>

using std::string;
using std::vector;

class BarBase {
  public:
    explicit BarBase(OhlcVector bar_series);

    OhlcVector::iterator cur_bar;
    const string *date = nullptr;
    const double *open = nullptr;
    const double *high = nullptr;
    const double *low = nullptr;
    const double *close = nullptr;
    const double *volume = nullptr;

    void next();

  private:
    OhlcVector _bar_series;
    void _set_ohlc();
};
