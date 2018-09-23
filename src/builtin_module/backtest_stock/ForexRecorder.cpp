#include "Environment.h"
#include "builtin_module/backtest_stock/ForexRecorder.h"
#include "builtin_module/backtest_stock/ForexSeries.h"
#include "sys_module/components/MatchEngine.h"
#include "sys_module/components/TradeLogGenerator.h"
#include "sys_module/models/BarBase.h"

OP_NAMESPACE_START

ForexRecorder::ForexRecorder()
    : RecorderBase::RecorderBase() {
    auto module = make_shared<ForexRecorder>(*this);
    env->save_module("ForexRecorder", module);
};

shared_ptr<BarBase> ForexRecorder::bar_class(const string &ticker,
                                             const string &frequency) {
    return make_shared<BarBase>(ticker, frequency);
};

void ForexRecorder::initialize() {
    match_engine->log_generator->initialize(env->instrument);

    holding_pnl = make_shared<HoldingPnlSeriesForex>();
    realized_pnl = make_shared<RealizedPnlSeriesForex>();
    commission = make_shared<CommissionSeriesForex>();
    market_value = make_shared<MarketValueSeriesForex>();
    margin = make_shared<MarginSeriesForex>();

    position = make_shared<PositionSeries>();
    avg_price = make_shared<AvgPriceSeries>();

    cash = make_shared<MoneySeries>("cash", initial_cash);
    frozen_cash = make_shared<MoneySeries>("frozen_cash", 0);
    balance = make_shared<MoneySeries>("balance", initial_cash);
};

void ForexRecorder::_update_cash(const string &trading_date) {

    const double new_balance = balance->latest();
    const double new_frozen_cash = margin->total_value();
    const double new_cash = new_balance - new_frozen_cash; // 更新cash

    frozen_cash->push_back(SeriesStruct{trading_date, new_frozen_cash});
    cash->push_back(SeriesStruct{trading_date, new_cash});
};
void ForexRecorder::set_setting(const double initial_cash_,
                                const double comm_,
                                const double comm_pct_,
                                const double margin_rate_) {
    initial_cash = initial_cash_;
    per_comm = comm_;
    per_comm_pct = comm_pct_;
    margin_rate = margin_rate_;
};

OP_NAMESPACE_END
