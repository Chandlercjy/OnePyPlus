#include "OP_DECLARE.h"

#pragma once

OP_NAMESPACE_START

enum class ActionType;
class SignalBase;
class Environment;
class SignalGenerator {
  public:
    SignalGenerator();
    Environment *env;
    void buy_or_short(map<string, double> &info,
                      const string &ticker,
                      const string &strategy_name,
                      const ActionType &action_type);
    void sell_or_cover(map<string, double> &info,
                       const string &ticker,
                       const string &strategy_name,
                       const ActionType &action_type);
    void cancel_tst(const string &strategy_name,
                    const string &ticker,
                    const string &long_or_short,
                    const bool takeprofit = false,
                    const bool stoploss = false,
                    const bool trailingstop = false);
    void cancel_pending(const string &strategy_name,
                        const string &ticker,
                        const string &long_or_short,
                        const double below_price = 0,
                        const double above_price = 0);

  private:
    const double _settle_price_pct(const string &ticker,
                                   double price,
                                   const double price_pct);
};

OP_NAMESPACE_END
