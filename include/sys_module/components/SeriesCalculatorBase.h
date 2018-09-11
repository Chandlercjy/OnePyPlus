#include "DataType.h"

#pragma once

OP_NAMESPACE_START
class Environment;

class SeriesCalculatorBase {
  public:
    SeriesCalculatorBase();
    Environment *env;

    void initialize_series(SeriesDict &series);
    void change_initial_value(SeriesDict &series,
                              const string &ticker,
                              const double value,
                              const string &long_or_short);
    double get_total_value(SeriesDict &series);

    void update_position(SeriesDict &series,
                         const string &ticker,
                         const double size,
                         const ActionType &action_type,
                         const double last_position,
                         const string &long_or_short);

    void update_avg_price(SeriesDict &series,
                          const string &ticker,
                          const double size,
                          const double execute_price,
                          const double last_position,
                          const double last_avg_price,
                          const double new_position,
                          const string &long_or_short);

    void update_money(SeriesVector &series,
                      const string &trading_date,
                      const double value);

    virtual void update_realized_pnl(SeriesDict &series,
                                     const string &ticker,
                                     const double size,
                                     const double execute_price,
                                     const ActionType &action_type,
                                     const double last_avg_price,
                                     const string &long_or_short) = 0;
    virtual void update_commission(SeriesDict &series,
                                   const string &ticker,
                                   const double size,
                                   const double execute_price,
                                   const ActionType &action_type,
                                   const double last_commission,
                                   const string &long_or_short) = 0;
    virtual void uodate_holding_pnl(SeriesDict &series,
                                    const string &ticker,
                                    const double cur_price,
                                    const double new_avg_price,
                                    const double new_position,
                                    const string &long_or_short) = 0;
    virtual void update_market_value(SeriesDict &series,
                                     const string &ticker,
                                     const double cur_price,
                                     const double new_position,
                                     const string &long_or_short) = 0;
    virtual void update_margin(SeriesDict &series,
                               const string &ticker,
                               const string &long_or_short) = 0;

    virtual void uodate_holding_pnl_barly(const bool order_executed) = 0;
    virtual void update_market_value_barly(const bool order_executed) = 0;
    virtual void update_margin_barly(const bool order_executed) = 0;

    static double get_latest(SeriesDict &series,
                             const string &ticker,
                             const string &long_or_short);

  protected:
    void _append_value(SeriesDict &series,
                       const string &ticker,
                       const double value,
                       const string &long_or_short);
    const int _direction(const ActionType &action_type);
};

OP_NAMESPACE_END
