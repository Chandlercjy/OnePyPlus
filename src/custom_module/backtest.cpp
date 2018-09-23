#include "Environment.h"
#include "OnePy.h"
#include "builtin_module/backtest/StockBroker.h"
#include "builtin_module/backtest/StockRecorder.h"

OP_NAMESPACE_START

using namespace op;

OnePiece stock(const vector<string> &ticker_list,
               const string &frequency,
               const double initial_cash,
               const string &start,
               const string &end,
               const string &broker_name) {
    OnePiece go;
    go.set_stock_backtest(initial_cash, 0, 0.0016, 0.1);
    go.set_date(start, end, frequency, "A_shares");
    return go;
};

OnePiece forex(const vector<string> &ticker_list,
               const string &frequency,
               const double initial_cash,
               const string &start,
               const string &end,
               const string &broker_name) {
    OnePiece go;
    go.set_forex_backtest(initial_cash, 0.02);
    go.set_date(start, end, frequency, "Forex");
    return go;
};

OP_NAMESPACE_END

