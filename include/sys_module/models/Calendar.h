#include "OP_DECLARE.h"

#pragma once

OP_NAMESPACE_START

class Environment;

class Calendar {
  public:
    Calendar();
    Environment *env = nullptr;
    void update_calendar();
    void initialize(const string &instrument);

  private:
    string _instrument;

    bool _is_forex_trading_time(string date_str);
    bool _is_A_shares_trading_time(string date_str);
    void _check_todate();

    using Is_func_ptr = bool (Calendar::*)(string date_str);
    Is_func_ptr _is_trading_time;
};

OP_NAMESPACE_END
