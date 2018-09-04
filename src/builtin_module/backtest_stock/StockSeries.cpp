#include "Constants.h"
#include "Environment.h"
#include "builtin_module/backtest_stock/StockSeries.h"
#include "sys_module/RecorderBase.h"

OP_NAMESPACE_START

void RealizedPnlSeries::update_order(const string &ticker,
                                     const double size,
                                     const double execute_price,
                                     const ActionType &action_type,
                                     const double last_avg_price,
                                     const string &long_or_short) {

    double new_value = 0;

    if (action_type == ActionType::Sell)
        new_value = (latest(ticker, long_or_short) +
                     (execute_price - last_avg_price) * size);
    else if (action_type == ActionType::Cover)
        new_value = (latest(ticker, long_or_short) -
                     (execute_price - last_avg_price) * size);

    if (new_value)
        _append_value(ticker, new_value, long_or_short);
}

void CommissionSeries::update_order(const string &ticker,
                                    const double size,
                                    const double execute_price,
                                    const ActionType &action_type,
                                    const double last_commission,
                                    const string &long_or_short) {

    const double per_comm = env->recorder->per_comm;
    const double per_comm_pct = env->recorder->per_comm_pct;
    double new_value = 0;

    if (action_type == ActionType::Buy || action_type == ActionType::Short) {
        if (per_comm_pct) {
            new_value = last_commission + per_comm_pct * size * execute_price;
        } else {
            new_value = last_commission + per_comm * size / 100;
        }
    }

    _append_value(ticker, new_value, long_or_short);
}

void HoldingPnlSeries::update_order(const string &ticker,
                                    const double cur_price,
                                    const double new_avg_price,
                                    const double new_position,
                                    const string &long_or_short) {
    double new_value = 0;
    if (new_position == 0) {
        new_value = 0;
    } else {
        int earn_short = (long_or_short == "long") ? 1 : -1;
        new_value = ((cur_price - new_avg_price) * new_position * earn_short);
    };
    _append_value(ticker, new_value, long_or_short);
}

void HoldingPnlSeries::update_barly(const bool order_executed) {
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

void MarketValueSeries::update_order(const string &ticker,
                                     const double cur_price,
                                     const double new_position,
                                     const string &long_or_short) {
    double new_value = new_position * cur_price;
    _append_value(ticker, new_value, long_or_short);
}

void MarketValueSeries::update_barly(const bool order_executed) {
    for (auto &ticker : env->tickers) {
        auto cur_price = get_barly_cur_price(ticker, order_executed);
        for (auto &long_or_short : {"long", "short"}) {
            double new_position = env->recorder->position->latest(
                ticker, long_or_short);

            update_order(ticker, cur_price, new_position, long_or_short);
        }
    }
}

void MarginSeries::update_order(const string &ticker,
                                const string &long_or_short) {

    if (long_or_short == "short") {
        auto new_value = env->recorder->market_value->latest(
                             ticker, long_or_short) *
                         env->recorder->margin_rate;
        _append_value(ticker, new_value, long_or_short);
    };
}

void MarginSeries::update_barly() {

    for (auto &ticker : env->tickers)
        for (auto &long_or_short : {"long", "short"})
            update_order(ticker, long_or_short);
}

OP_NAMESPACE_END


