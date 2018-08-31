#include "sys_module/models/Calendar.h"
#include <map>
#include <string>
#include <vector>

#pragma once

namespace op {
using std::string;
using std::unique_ptr;

class Calendar;
class Environment;
class BarBase;

class MarketMaker {
  public:
    MarketMaker();
    Environment *env;
    void update_market();
    void initialize();

  private:
    unique_ptr<Calendar> calendar;
    void _initialize_calendar();
    void _initialize_feeds();
    void _initialize_cleaners();
    void _check_initialize_status() const;
    void _update_recorder(bool backtest_finished = false);
    void _check_blowup() const;
    void _update_bar();
    std::shared_ptr<BarBase> get_bar(const string &ticker, const string &frequency);
};
} // namespace op

