#include "OP_DECLARE.h"

#pragma once

OP_NAMESPACE_START

class SignalChecker;
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
    void cancel_tst(const string &ticker,
                    const string &strategy_name,
                    const string &long_or_short,
                    const bool takeprofit,
                    const bool stoploss,
                    const bool trailingstop);
    void cancel_pending(const string &ticker,
                        const string &strategy_name,
                        const string &long_or_short,
                        const double below_price,
                        const double above_price);

  private:
    const double _settle_price_pct(const string &ticker,
                                   double price,
                                   const double price_pct);
    shared_ptr<SignalChecker> _signal_checker;

    template <typename T>
    void _generate_signal(const T &signal);
};

OP_NAMESPACE_END
