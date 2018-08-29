#include "../Constants.h"
#include "../Environment.h"
#include "StrategyBase.h"
#include "components/SignalGenerator.h"

namespace sys {
StrategyBase::StrategyBase()
    : env(Environment::get_instance()),
      _signal_generator(std::make_shared<SignalGenerator>()){};

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
                                    get_name(),
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
                                     get_name(),
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
                                    get_name(),
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
                                     get_name(),
                                     ActionType::Cover);
};

void StrategyBase::run() {
    handle_bar();
};

template <typename T>
void StrategyBase::save_to_env(const T *self_ptr, const string &name) {
    env->strategies[name] = std::make_shared<T>(*self_ptr);
}
} // namespace sys
