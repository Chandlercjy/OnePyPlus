#include "DataType.h"
#include "OP_DECLARE.h"
#include <string>
#include <vector>

#pragma once

OP_NAMESPACE_START

class Environment;

class BarBase {
  public:
    BarBase();
    Environment *env;

    explicit BarBase(const string &ticker, const string &frequency);

    const string ticker;
    const string frequency;

    OhlcVector::const_iterator previous_ohlc;
    OhlcVector::const_iterator current_ohlc;
    OhlcVector::const_iterator next_ohlc;

    const string date() const;
    const double open() const;
    const double high() const;
    const double low() const;
    const double close() const;
    const double volume() const;

    const double cur_price() const;
    const double execute_price() const;

    bool initialize(int buffer_day);
    void next();
    void next_directly();

    bool is_suspended();
    void move_next_ohlc_to_cur_ohlc();

    bool is_bar_series_end() const;

  private:
    OhlcVector::const_iterator _iter_data;
    shared_ptr<OhlcVector> _bar_series = nullptr;
    inline void _update_iter_data(const string &start, const string &end);
    inline void _delete_ohlc(const string &msg);
};

OP_NAMESPACE_END
