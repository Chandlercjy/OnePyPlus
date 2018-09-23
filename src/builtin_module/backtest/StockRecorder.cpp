#include "Environment.h"
#include "builtin_module/backtest/StockRecorder.h"
#include "builtin_module/backtest/StockSeries.h"
#include "sys_module/components/MatchEngine.h"
#include "sys_module/components/TradeLogGenerator.h"
#include "sys_module/models/BarBase.h"

OP_NAMESPACE_START
using std::make_shared;
using std::shared_ptr;

StockRecorder::StockRecorder()
    : RecorderBase::RecorderBase() {
    auto module = make_shared<StockRecorder>(*this);
    env->save_module("StockRecorder", module);
};

shared_ptr<BarBase> StockRecorder::bar_class(const string &ticker,
                                             const string &frequency) {
    return make_shared<BarBase>(ticker, frequency);
};

void StockRecorder::initialize() {
    match_engine->log_generator->initialize(env->instrument);

    holding_pnl = make_shared<HoldingPnlSeriesStock>();
    realized_pnl = make_shared<RealizedPnlSeriesStock>();
    commission = make_shared<CommissionSeriesStock>();
    market_value = make_shared<MarketValueSeriesStock>();
    margin = make_shared<MarginSeriesStock>();
    position = make_shared<PositionSeries>();
    avg_price = make_shared<AvgPriceSeries>();

    cash = make_shared<MoneySeries>("cash", initial_cash);
    frozen_cash = make_shared<MoneySeries>("frozen_cash", 0);
    balance = make_shared<MoneySeries>("balance", initial_cash);
};

void StockRecorder::_update_cash(const string &trading_date) {

    const double total_margin = margin->total_value();
    const double total_market_value = market_value->total_value();
    const double new_balance = balance->latest();
    const double new_frozen_cash = total_margin + total_market_value; // 更新frozen_cash
    const double new_cash = new_balance - new_frozen_cash;            // 更新cash

    frozen_cash->push_back(SeriesStruct{trading_date, new_frozen_cash});
    cash->push_back(SeriesStruct{trading_date, new_cash});
};
void StockRecorder::set_setting(const double initial_cash_,
                                const double comm_,
                                const double comm_pct_,
                                const double margin_rate_) {
    initial_cash = initial_cash_;
    per_comm = comm_;
    per_comm_pct = comm_pct_;
    margin_rate = margin_rate_;
};

OP_NAMESPACE_END
