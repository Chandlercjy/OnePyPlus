#include "sys_module/components/SeriesCalculatorBase.h"

#pragma once

OP_NAMESPACE_START

class StockSeriesCalculator : public SeriesCalculatorBase {
  public:
    void update_realized_pnl(SeriesDict &series,
                             const string &ticker,
                             const double size,
                             const double execute_price,
                             const ActionType &action_type,
                             const double last_avg_price,
                             const string &long_or_short) override;
    void update_commission(SeriesDict &series,
                           const string &ticker,
                           const double size,
                           const double execute_price,
                           const ActionType &action_type,
                           const double last_commission,
                           const string &long_or_short) override;
    void uodate_holding_pnl(SeriesDict &series,
                            const string &ticker,
                            const double cur_price,
                            const double new_avg_price,
                            const double new_position,
                            const string &long_or_short) override;
    void update_market_value(SeriesDict &series,
                             const string &ticker,
                             const double cur_price,
                             const double new_position,
                             const string &long_or_short) override;
    void update_margin(SeriesDict &series,
                       const string &ticker,
                       const string &long_or_short) override;

    void uodate_holding_pnl_barly(const bool order_executed) override;
    void update_market_value_barly(const bool order_executed) override;
    void update_margin_barly(const bool order_executed) override;

    double get_barly_cur_price(const string &ticker,
                               const bool order_executed);
};

OP_NAMESPACE_END
