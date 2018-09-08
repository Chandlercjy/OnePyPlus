#include "OP_DECLARE.h"

#pragma once

OP_NAMESPACE_START

class Environment;
class SignalGenerator;

class StrategyBase {

  public:
    StrategyBase();
    Environment *env;
    void buy(const double size,
             const string &ticker,
             const double takeprofit = 0,
             const double takeprofit_pct = 0,
             const double stoploss = 0,
             const double stoploss_pct = 0,
             const double trailingstop = 0,
             const double trailingstop_pct = 0,
             const double price = 0,
             const double price_pct = 0);
    void sell(const double size,
              const string &ticker,
              const double price = 0,
              const double price_pct = 0);
    void shortsell(const double size,
                   const string &ticker,
                   const double takeprofit = 0,
                   const double takeprofit_pct = 0,
                   const double stoploss = 0,
                   const double stoploss_pct = 0,
                   const double trailingstop = 0,
                   const double trailingstop_pct = 0,
                   const double price = 0,
                   const double price_pct = 0);
    void cover(const double size,
               const string &ticker,
               const double price = 0,
               const double price_pct = 0);

    void cancel_pending(const string &ticker,
                        const string &long_or_short,
                        const double below_price = 0,
                        const double above_price = 0);

    void cancel_tst(const string &ticker,
                    const string &long_or_short,
                    const bool takeprofit = false,
                    const bool stoploss = false,
                    const bool trailingstop = false);

    virtual void handle_bar(){};
    void run();

    //protected:
    virtual const string get_name() = 0;

  private:
    shared_ptr<SignalGenerator> _signal_generator;
};

OP_NAMESPACE_END
