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

    explicit BarBase(const string &ticker, const string &frequency);

    const string frequency;
    const string ticker;

    OhlcVector::const_iterator previous_bar;
    OhlcVector::const_iterator current_bar;
    OhlcVector::const_iterator next_bar;

    const string date();
    const double open();
    const double high();
    const double low();
    const double close();
    const double volume();

    const double cur_price();
    const double execute_price();

    void initialize(int &buffer_day);
    void next();
    void next_directly();

    bool is_suspended();
    void move_next_ohlc_to_cur_ohlc();
    virtual ~BarBase() = default;

  private:
    OhlcVector *_iter_data;
    inline void _update_iter_data();
    inline void _delete_ohlc();
};
} // namespace sys
