#include "Constants.h"
#include "Environment.h"
#include "builtin_module/backtest/ForexSeries.h"
#include "sys_module/RecorderBase.h"
#include "utils/easy_func.h"

OP_NAMESPACE_START

using ForexUtils = utils::ForexUtils;

void RealizedPnlSeriesForex::update_order(const string &ticker,
                                          const double size,
                                          const double execute_price,
                                          const ActionType &action_type,
                                          const double last_avg_price,
                                          const string &long_or_short) {

    double new_value = 0;

    if (action_type == ActionType::Sell)
        new_value = (latest(ticker, long_or_short) +
                     (execute_price - last_avg_price) * size *
                         ForexUtils::dollar_per_pips(ticker, execute_price));
    else if (action_type == ActionType::Cover)
        new_value = (latest(ticker, long_or_short) -
                     (execute_price - last_avg_price) * size *
                         ForexUtils::dollar_per_pips(ticker, execute_price));

    if (new_value)
        _append_value(ticker, new_value, long_or_short);
}

void CommissionSeriesForex::update_order(const string &ticker,
                                         const double size,
                                         const double execute_price,
                                         const ActionType &action_type,
                                         const double last_commission,
                                         const string &long_or_short) {

    auto slippage = utils::Forex_slippage[ticker];

    if (action_type == ActionType::Buy || action_type == ActionType::Short) {
        auto new_value = (last_commission +
                          slippage * size / 1e5 *
                              ForexUtils::dollar_per_pips(ticker, execute_price));
        _append_value(ticker, new_value, long_or_short);
    }
}

void HoldingPnlSeriesForex::update_order(const string &ticker,
                                         const double cur_price,
                                         const double new_avg_price,
                                         const double new_position,
                                         const string &long_or_short) {
    double new_value = 0;
    if (new_position == 0) {
        new_value = 0;
    } else {
        int earn_short = (long_or_short == "long") ? 1 : -1;
        new_value = ((cur_price - new_avg_price) * new_position * earn_short *
                     ForexUtils::dollar_per_pips(ticker, cur_price));
    };
    _append_value(ticker, new_value, long_or_short);
}

void HoldingPnlSeriesForex::update_barly(const bool order_executed) {
    for (auto &ticker : env->tickers) {
        auto cur_price = get_barly_cur_price(ticker, order_executed);
        for (auto &long_or_short : {"long", "short"}) {
            double new_position = env->recorder->position->latest(
                ticker, long_or_short);
            double new_avg_price = env->recorder->avg_price->latest(
                ticker, long_or_short);

            update_order(ticker, cur_price, new_avg_price,
                         new_position, long_or_short);
        }
    }
}

void MarketValueSeriesForex::update_order(const string &ticker,
                                          const double cur_price,
                                          const double new_position,
                                          const string &long_or_short) {
    double new_value = (new_position *
                        ForexUtils::market_value_multiplyer(ticker, cur_price));
    _append_value(ticker, new_value, long_or_short);
}

void MarketValueSeriesForex::update_barly(const bool order_executed) {
    for (auto &ticker : env->tickers) {
        auto cur_price = get_barly_cur_price(ticker, order_executed);
        for (auto &long_or_short : {"long", "short"}) {
            double new_position = env->recorder->position->latest(
                ticker, long_or_short);
            update_order(ticker, cur_price, new_position, long_or_short);
        }
    }
}

void MarginSeriesForex::update_order(const string &ticker,
                                     const string &long_or_short) {

    auto new_value = env->recorder->market_value->latest(
                         ticker, long_or_short) *
                     env->recorder->margin_rate;
    _append_value(ticker, new_value, long_or_short);
}

void MarginSeriesForex::update_barly() {

    for (auto &ticker : env->tickers)
        for (auto &long_or_short : {"long", "short"})
            update_order(ticker, long_or_short);
}

OP_NAMESPACE_END
