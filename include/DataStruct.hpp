#include "OP_DECLARE.h"

#pragma once

OP_NAMESPACE_START
struct OhlcStruct {
    OhlcStruct(const string &date, const double open, const double high,
               const double low, const double close, const double volume)
        : date(date),
          open(open),
          high(high),
          low(low),
          close(close),
          volume(volume){};
    const string date;
    const double open;
    const double high;
    const double low;
    const double close;
    const double volume;
};

struct CleanerDataStruct {
    CleanerDataStruct(const string &ticker)
        : ticker(ticker){};
    CleanerDataStruct(){};
    string ticker;
    deque<string> date;
    deque<double> open;
    deque<double> high;
    deque<double> low;
    deque<double> close;
    deque<double> volume;
    void clear() {
        date.clear();
        open.clear();
        high.clear();
        low.clear();
        close.clear();
        volume.clear();
    };
};

struct SeriesStruct {
    const string date;
    double value;
};

struct TradeLogStruct {
    TradeLogStruct(const string &ticker,
                   const string &entry_date,
                   const string &exit_date,
                   const double entry_price,
                   const double exit_price,
                   const string &entry_type,
                   const string &exit_type,
                   const double pl_points,
                   const double size,
                   const double re_pnl,
                   const double commission)
        : ticker(ticker),
          entry_date(entry_date),
          exit_date(exit_date),
          entry_price(entry_price),
          exit_price(exit_price),
          entry_type(entry_type),
          exit_type(exit_type),
          pl_points(pl_points),
          size(size),
          re_pnl(re_pnl),
          commission(commission){};

    const string ticker;
    const string entry_date;
    const string exit_date;
    const double entry_price;
    const double exit_price;
    const string entry_type;
    const string exit_type;
    const double pl_points;
    const double size;
    const double re_pnl;
    const double commission;
};
OP_NAMESPACE_END
