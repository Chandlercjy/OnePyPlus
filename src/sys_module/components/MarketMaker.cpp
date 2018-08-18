#include "../models/Calendar.h"
#include "MarketMaker.h"

namespace sys {

void MarketMaker::initialize(){};
void MarketMaker::_initialize_calendar() {
    calendar = Calendar(env->instrument);
};

void MarketMaker::_initialize_feeds(){};
void MarketMaker::_initialize_cleaners(){};
void MarketMaker::_update_recorder(bool backtest_finished){};
void MarketMaker::_check_blowup(){};
void MarketMaker::_update_bar(){};

BarBase *MarketMaker::get_bar(string &ticker, string &frequency){};
} // namespace sys
