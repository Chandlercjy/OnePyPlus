#include "OP_DECLARE.h"
#include "sys_module/models/Calendar.h"

#pragma once

OP_NAMESPACE_START

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

OP_NAMESPACE_END
