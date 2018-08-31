#include "Environment.h"
#include "Exceptions.h"
#include "sys_module/components/SignalGenerator.h"
#include "sys_module/models/BarBase.h"
#include "sys_module/models/Signal.h"
#include "sys_module/models/SignalCancel.h"
#include "utils/utils.h"

namespace op {

SignalGenerator::SignalGenerator() : env(Environment::get_instance()){};

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

void SignalGenerator::buy_or_short(map<string, double> &info,
                                   const string &ticker,
                                   const string &strategy_name,
                                   const ActionType &action_type) {
    const double exact_price = _settle_price_pct(ticker, info["price"], info["price_pct"]);
    if (exact_price != 0) {
        info["price"] = exact_price;
        info["price_pct"] = 0;
        SignalForPending signal{info, ticker, strategy_name, action_type};
    } else if (utils::is_elem_in_vector(env->cur_suspended_tickers, ticker)) {
    } else {
        Signal signal{info, ticker, strategy_name, action_type};
    }
}

void SignalGenerator::sell_or_cover(map<string, double> &info,
                                    const string &ticker,
                                    const string &strategy_name,
                                    const ActionType &action_type) {
    const double exact_price = _settle_price_pct(ticker, info["price"], info["price_pct"]);
    if (exact_price != 0) {
        info["price"] = exact_price;
        info["price_pct"] = 0;
        SignalForPending signal{info, ticker, strategy_name, action_type};
    } else if (utils::is_elem_in_vector(env->cur_suspended_tickers, ticker)) {
    } else {
        Signal signal{info, ticker, strategy_name, action_type};
    }
}

void SignalGenerator::cancel_tst(const string &strategy_name,
                                 const string &ticker,
                                 const string &long_or_short,
                                 const bool takeprofit,
                                 const bool stoploss,
                                 const bool trailingstop) {
    if (long_or_short != "long" && long_or_short != "short")
        throw std::logic_error("long_or_short should be long or short!");

    SignalCancelTST signal{strategy_name,
                           ticker,
                           long_or_short,
                           takeprofit,
                           stoploss,
                           trailingstop};
}

void SignalGenerator::cancel_pending(const string &strategy_name,
                                     const string &ticker,
                                     const string &long_or_short,
                                     const double below_price,
                                     const double above_price) {

    if (long_or_short != "long" && long_or_short != "short")
        throw std::logic_error("long_or_short should be long or short!");

    SignalCancelPending signal{strategy_name,
                               ticker,
                               long_or_short,
                               below_price,
                               above_price};
}

} // namespace op

