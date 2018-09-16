#include "Constants.h"
#include "Environment.h"
#include "sys_module/StrategyBase.h"
#include "sys_module/components/SignalGenerator.h"

OP_NAMESPACE_START
StrategyBase::StrategyBase(const string &name)
    : env(Environment::get_instance()),
      name(name),
      _signal_generator(make_shared<SignalGenerator>()){};

void StrategyBase::buy(const double size,
                       const string &ticker,
                       const double takeprofit,
                       const double takeprofit_pct,
                       const double stoploss,
                       const double stoploss_pct,
                       const double trailingstop,
                       const double trailingstop_pct,
                       const double price,
                       const double price_pct) {
    map<string, double> info = {
        {"size", size},
        {"takeprofit", takeprofit},
        {"takeprofit_pct", takeprofit_pct},
        {"stoploss", stoploss},
        {"stoploss_pct", stoploss_pct},
        {"trailingstop", trailingstop},
        {"trailingstop_pct", trailingstop_pct},
        {"price", price},
        {"price_pct", price_pct},
    };

    _signal_generator->buy_or_short(info,
                                    ticker,
                                    name,
                                    ActionType::Buy);
};

void StrategyBase::sell(const double size,
                        const string &ticker,
                        const double price,
                        const double price_pct) {

    map<string, double> info = {
        {"size", size},
        {"takeprofit", 0},
        {"takeprofit_pct", 0},
        {"stoploss", 0},
        {"stoploss_pct", 0},
        {"trailingstop", 0},
        {"trailingstop_pct", 0},
        {"price", price},
        {"price_pct", price_pct},
    };

    _signal_generator->sell_or_cover(info,
                                     ticker,
                                     name,
                                     ActionType::Sell);
};

void StrategyBase::shortsell(const double size,
                             const string &ticker,
                             const double takeprofit,
                             const double takeprofit_pct,
                             const double stoploss,
                             const double stoploss_pct,
                             const double trailingstop,
                             const double trailingstop_pct,
                             const double price,
                             const double price_pct) {
    map<string, double> info = {
        {"size", size},
        {"takeprofit", takeprofit},
        {"takeprofit_pct", takeprofit_pct},
        {"stoploss", stoploss},
        {"stoploss_pct", stoploss_pct},
        {"trailingstop", trailingstop},
        {"trailingstop_pct", trailingstop_pct},
        {"price", price},
        {"price_pct", price_pct},
    };
    _signal_generator->buy_or_short(info,
                                    ticker,
                                    name,
                                    ActionType::Short);
};

void StrategyBase::cover(const double size,
                         const string &ticker,
                         const double price,
                         const double price_pct) {

    map<string, double> info = {
        {"size", size},
        {"takeprofit", 0},
        {"takeprofit_pct", 0},
        {"stoploss", 0},
        {"stoploss_pct", 0},
        {"trailingstop", 0},
        {"trailingstop_pct", 0},
        {"price", price},
        {"price_pct", price_pct},
    };
    _signal_generator->sell_or_cover(info,
                                     ticker,
                                     name,
                                     ActionType::Cover);
};

void StrategyBase::cancel_pending(const string &ticker,
                                  const string &long_or_short,
                                  const double below_price,
                                  const double above_price) {

    _signal_generator->cancel_pending(ticker,
                                      name,
                                      long_or_short,
                                      below_price,
                                      above_price);
};

void StrategyBase::cancel_tst(const string &ticker,
                              const string &long_or_short,
                              const bool takeprofit,
                              const bool stoploss,
                              const bool trailingstop) {
    _signal_generator->cancel_tst(ticker,
                                  name,
                                  long_or_short,
                                  takeprofit,
                                  stoploss,
                                  trailingstop);
};

void StrategyBase::run() {
    handle_bar();
};

OP_NAMESPACE_END
