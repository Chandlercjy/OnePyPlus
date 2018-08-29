#include "../../DataType.h"
#include <map>
#include <string>
#include <vector>

#pragma once

namespace sys {
using std::map;
using std::string;
using std::vector;
class Environment;
enum class ActionType;

class SeriesBase {
  public:
    SeriesBase();
    Environment *env;

    virtual const string get_name() = 0;

    void change_initial_value(const string &ticker,
                              const double value,
                              const string &long_or_short);
    double latest(const string &ticker,
                  const string &long_or_short);
    double total_value();

  protected:
    map<string, vector<SeriesStruct>> _data;

    void _append_value(const string &ticker,
                       const double value,
                       const string &long_or_short);
    double get_barly_cur_price(const string &ticker,
                               const bool order_executed);

  private:
    void _initialize_data();
};

class MoneySeries final {
  public:
    MoneySeries(const string &name, const double initial_value);
    const string get_name();

    void change_initial_value(const double value);
    double latest();

  private:
    const string _name;
    vector<SeriesStruct> _data;
};

class PositionSeries : public SeriesBase {
  public:
    using SeriesBase::SeriesBase;

    virtual void update_order(const string &ticker,
                              const double size,
                              const ActionType &action_type,
                              const double last_position,
                              const string &long_or_short);

    const string get_name() override { return "position"; };

  private:
    const int _direction(const ActionType &action_type);
};

class AvgPriceSeries : public SeriesBase {
  public:
    using SeriesBase::SeriesBase;

    virtual void update_order(const string &ticker,
                              const double size,
                              const double execute_price,
                              const double last_position,
                              const double last_avg_price,
                              const double new_position,
                              const string &long_or_short);
    const string get_name() override { return "avg_price"; };
};

class RealizedPnlSeriesBase : public SeriesBase {
  public:
    using SeriesBase::SeriesBase;

    virtual void update_order(const string &ticker,
                              const double size,
                              const double execute_price,
                              const ActionType &action_type,
                              const double last_avg_price,
                              const string &long_or_short) = 0;
    const string get_name() override { return "realized_pnl"; };
};

class CommissionSeriesBase : public SeriesBase {
  public:
    using SeriesBase::SeriesBase;
    virtual void update_order(const string &ticker,
                              const double size,
                              const double execute_price,
                              const ActionType &action_type,
                              const double last_commission,
                              const string &long_or_short) = 0;
    const string get_name() override { return "commission"; };
};

class HoldingPnlSeriesBase : public SeriesBase {
  public:
    using SeriesBase::SeriesBase;
    virtual void update_order(const string &ticker,
                              const double cur_price,
                              const double new_avg_price,
                              const double new_position,
                              const string &long_or_short) = 0;
    virtual void update_barly(const bool order_executed) = 0;
    const string get_name() override { return "holding_pnl"; };
};

class MarketValueSeriesBase : public SeriesBase {
  public:
    using SeriesBase::SeriesBase;
    virtual void update_order(const string &ticker,
                              const double cur_price,
                              const double new_position,
                              const string &long_or_short) = 0;
    virtual void update_barly(const bool order_executed) = 0;
    const string get_name() override { return "market_value"; };
};

class MarginSeriesBase : public SeriesBase {
  public:
    using SeriesBase::SeriesBase;
    virtual void update_order(const string &ticker,
                              const string &long_or_short) = 0;

    virtual void update_barly() = 0;
    const string get_name() override { return "margin"; };
};

} // namespace sys
