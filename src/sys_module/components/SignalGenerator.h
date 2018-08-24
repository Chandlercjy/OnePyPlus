#include <string>

#pragma once

namespace sys {
using std::string;

enum class ActionType;
class SignalBase;
class Environment;
class SignalGenerator {
  public:
    SignalGenerator(const string &strategy_name,
                    const ActionType &action_type);
    Environment *env;
    void buy_or_short(const double size,
                      const string &ticker,
                      const double takeprofit,
                      const double takeprofit_pct,
                      const double stoploss,
                      const double stoploss_pct,
                      const double trailingstop,
                      const double trailingstop_pct,
                      const double price,
                      const double price_pct);
    void sell_or_cover(const double size,
                       const string &ticker,
                       const double price,
                       const double price_pct);
    void cancel_tst(const string &ticker,
                    const string &long_or_short,
                    const bool takeprofit = false,
                    const bool stoploss = false,
                    const bool trailingstop = false);
    void cancel_pending(const string &ticker,
                        const string &long_or_short,
                        const double below_price = 0,
                        const double above_price = 0);

  private:
    const string _strategy_name;
    const ActionType _action_type;
    const double _settle_price_pct(const string &ticker,
                                   double price,
                                   const double price_pct);
};

} // namespace sys
