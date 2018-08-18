#include <string>
#pragma once
using std::string;
namespace sys {

class Environment;

class Calendar {
  public:
    explicit Calendar(const string &instrument);
    Environment *env;
    void update_calendar();

  private:
    string _instrument;
    bool (Calendar::*_is_trading_time)(string date_str);
    void _set_is_trading_time_func();
    bool _is_forex_trading_time(string date_str);
    bool _is_A_shares_trading_time(string date_str);
    void _check_todate();
};
} // namespace sys
