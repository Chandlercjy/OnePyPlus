#include "Constants.h"
#include "Environment.h"
#include "builtin_module/backtest_stock/StockSeriesCalculator.h"
#include "sys_module/RecorderBase.h"
#include "sys_module/models/BarBase.h"

OP_NAMESPACE_START
void StockSeriesCalculator::update_realized_pnl(SeriesDict &series,
                                                const string &ticker,
                                                const double size,
                                                const double execute_price,
                                                const ActionType &action_type,
                                                const double last_avg_price,
                                                const string &long_or_short) {
    double new_value = 0;

    if (action_type == ActionType::Sell)
        new_value = (get_latest(series, ticker, long_or_short) +
                     (execute_price - last_avg_price) * size);
    else if (action_type == ActionType::Cover)
        new_value = (get_latest(series, ticker, long_or_short) -
                     (execute_price - last_avg_price) * size);

    if (new_value)
        _append_value(series, ticker, new_value, long_or_short);
}

void StockSeriesCalculator::update_commission(SeriesDict &series,
                                              const string &ticker,
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

    _append_value(series, ticker, new_value, long_or_short);
}
void StockSeriesCalculator::uodate_holding_pnl(SeriesDict &series,
                                               const string &ticker,
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
    _append_value(series, ticker, new_value, long_or_short);
}
void StockSeriesCalculator::update_market_value(SeriesDict &series,
                                                const string &ticker,
                                                const double cur_price,
                                                const double new_position,
                                                const string &long_or_short) {
    double new_value = new_position * cur_price;
    _append_value(series, ticker, new_value, long_or_short);
}
void StockSeriesCalculator::update_margin(SeriesDict &series,
                                          const string &ticker,
                                          const string &long_or_short) {

    if (long_or_short == "short") {
        auto new_value = get_latest(env->recorder->market_value, ticker,
                                    long_or_short) *
                         env->recorder->margin_rate;
        _append_value(series, ticker, new_value, long_or_short);
    };
}

double StockSeriesCalculator::get_barly_cur_price(const string &ticker,
                                                  const bool order_executed) {
    if (order_executed) {
        return env->feeds[ticker]->execute_price();
    } else {
        return env->feeds[ticker]->open();
    }
};

OP_NAMESPACE_END
