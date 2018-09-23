#include "Environment.h"
#include "OP_DECLARE.h"
#include "OnePy.h"
#include "builtin_module/CsvReader.h"
#include "builtin_module/backtest/StockBroker.h"
#include "builtin_module/backtest/StockRecorder.h"
#include "sys_module/StrategyBase.h"

#pragma once

OP_NAMESPACE_START

const string START = "2018-03-07";
const string END = "2018-03-14";
const string INSTRUMENT = "A_shares";
const string TICKER = "000001";
const string BROKER = "tushare";
const string FREQUENCY = "D";

class DemoStrategy : public op::StrategyBase {
  public:
    DemoStrategy(const string &name)
        : StrategyBase(name) {
        auto module = std::make_shared<DemoStrategy>(*this);
        env->save_module(name, module);
    };

    void handle_bar() override{};
};

class SettingFunc {
  public:
    static void set_easy_context() {
        Environment *env = Environment::get_instance();
        env->fromdate = START;
        env->todate = END;
        env->sys_frequency = FREQUENCY;
        env->instrument = INSTRUMENT;
        env->initialize_env();
    };

    static OnePiece global_setting() {
        set_easy_context();
        CsvReader csv_reader("../data/", TICKER, TICKER);
        DemoStrategy demo_strategy("DemoStrategy");
        OnePiece go;
        go.set_stock_backtest(100000, 0, 0.0016, 0.1);
        go.set_date(START, END, FREQUENCY);
        go.initialize_trading_system();
        return go;
    };
};

OP_NAMESPACE_END
