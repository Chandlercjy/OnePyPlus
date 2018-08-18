#pragma once
#include "../models/BarBase.h"
#include "../../Environment.h"
namespace sys {

class Calendar;
class Environment;

class MarketMaker {
  public:
    const static Environment *env;
    static void update_market();
    static void initialize();

  private:
    static Calendar calendar;
    static void _initialize_calendar();
    static void _initialize_feeds();
    static void _initialize_cleaners();
    static void _update_recorder(bool backtest_finished = false);
    static void _check_blowup();
    static void _update_bar();
    static BarBase *get_bar(string &ticker, string &frequency);
    MarketMaker() = default;
};
const Environment *MarketMaker::env = Environment::get_instance();
} // namespace sys
