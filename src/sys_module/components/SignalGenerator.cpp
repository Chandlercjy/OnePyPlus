#include "../../Environment.h"
#include "../../Exceptions.h"
#include "../../utils/utils.h"
#include "../models/BarBase.h"
#include "../models/Signal.h"
#include "../models/SignalCancel.h"
#include "SignalGenerator.h"

namespace sys {

SignalGenerator::SignalGenerator(const string &strategy_name,
                                 const ActionType &action_type)
    : env(Environment::get_instance()),
      _strategy_name(strategy_name),
      _action_type(action_type){};

const double SignalGenerator::_settle_price_pct(const string &ticker,
                                                double price,
                                                const double price_pct) {
    if (price != 0 && price_pct != 0) {
        throw except::OrderConflictError();
    } else if (price_pct != 0) {
        price = (price_pct + 1) * (env->feeds[ticker]->cur_price());
    };
    return price;
};

void SignalGenerator::buy_or_short(const double size,
                                   const string &ticker,
                                   const double takeprofit,
                                   const double takeprofit_pct,
                                   const double stoploss,
                                   const double stoploss_pct,
                                   const double trailingstop,
                                   const double trailingstop_pct,
                                   const double price,
                                   const double price_pct) {
    const double exact_price = _settle_price_pct(ticker, price, price_pct);
    if (exact_price == 0) {
        SignalForPending signal{_strategy_name, _action_type, size, ticker,
                                takeprofit, takeprofit_pct, stoploss, stoploss_pct,
                                trailingstop, trailingstop_pct, exact_price};
    } else if (utils::is_elem_in_vector(env->tickers, ticker)) {
    } else {
        Signal signal{_strategy_name, _action_type, size, ticker,
                      takeprofit, takeprofit_pct, stoploss, stoploss_pct,
                      trailingstop, trailingstop_pct, exact_price};
    }
}

void SignalGenerator::sell_or_cover(const double size,
                                    const string &ticker,
                                    const double price,
                                    const double price_pct) {
    const double exact_price = _settle_price_pct(ticker, price, price_pct);
    Signal good_signal{_strategy_name, _action_type, size, ticker, exact_price,
                       0, 0, 0, 0, 0, 0};
}

void SignalGenerator::cancel_tst(const string &ticker,
                                 const string &long_or_short,
                                 const bool takeprofit,
                                 const bool stoploss,
                                 const bool trailingstop) {
    if (long_or_short != "long" && long_or_short != "short")
        throw std::logic_error("long_or_short should be long or short!");

    SignalCancelTST signal{_strategy_name,
                           ticker,
                           long_or_short,
                           takeprofit,
                           stoploss,
                           trailingstop};
}

void SignalGenerator::cancel_pending(const string &ticker,
                                     const string &long_or_short,
                                     const double below_price,
                                     const double above_price) {

    if (long_or_short != "long" && long_or_short != "short")
        throw std::logic_error("long_or_short should be long or short!");

    SignalCancelPending signal{_strategy_name,
                               ticker,
                               long_or_short,
                               below_price,
                               above_price};
}

} // namespace sys
