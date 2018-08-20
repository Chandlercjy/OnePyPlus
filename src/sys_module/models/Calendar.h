#include <string>
#pragma once
using std::string;
namespace sys {

class Environment;

class Calendar {
  public:
    Calendar();
    Environment *env = nullptr;
    void update_calendar();
    void initialize(const string &instrument);

  private:
    string _instrument;
    bool (Calendar::*_is_trading_time)(string date_str);
    bool _is_forex_trading_time(string date_str);
    bool _is_A_shares_trading_time(string date_str);
    void _check_todate();
};
} // namespace sys
