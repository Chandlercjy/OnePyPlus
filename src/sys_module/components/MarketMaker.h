#pragma once
#include "../models/BarBase.h"
namespace sys {

class MarketMaker {
  public:
    void update_market();
    void initialize();

  private:
    void _initialize_calendar();
    void _initialize_feeds();
    void _initialize_cleaners();
    void _update_recorder(bool backtest_finished = false);
    void _check_blowup();
    void _update_bar();
    BarBase *get_bar(string &ticker, string &frequency);
};
} // namespace sys
