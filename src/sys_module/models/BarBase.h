#pragma once

#include "../../DataType.h"
#include <string>
#include <vector>

namespace sys {
using std::string;
using std::vector;
class Environment;

class BarBase {
  public:
    BarBase();
    Environment *env;

    explicit BarBase(OhlcVector bar_series);

    OhlcVector::const_iterator previous_bar;
    OhlcVector::const_iterator cur_bar;
    OhlcVector::const_iterator next_bar;
    const string *date;
    const double *open;
    const double *high;
    const double *low;
    const double *close;
    const double *volume;

    const double execute_price();
    const double cur_price();

    void next();
    void next_directly();
    void initialize();

    bool is_suspended();
    void move_next_ohlc_to_cur_ohlc();

  private:
    OhlcVector _bar_series;
    inline void _update_iter_data();
    inline void _delete_ohlc();
};
} // namespace sys
