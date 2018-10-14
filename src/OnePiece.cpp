#include "OnePiece.h"
#include "Constants.h"
#include "Environment.h"
#include "EventEngine.h"
#include "Exceptions.h"
#include "builtin_module/backtest/ForexBroker.h"
#include "builtin_module/backtest/ForexRecorder.h"
#include "builtin_module/backtest/StockBroker.h"
#include "builtin_module/backtest/StockRecorder.h"
#include "config.h"
#include "sys_module/RecorderBase.h"
#include "sys_module/components/MarketMaker.h"
#include "sys_module/components/PendingOrderChecker.h"
#include <iostream>

OP_NAMESPACE_START

OnePiece::OnePiece()
    : env(op::Environment::get_instance()),
      market_maker(make_shared<op::MarketMaker>()),
      _pending_order_checker(make_shared<op::PendingOrderChecker>()),
      _event_loop(op::EVENT_LOOP){};

void OnePiece::sunny() {
    initialize_trading_system();
    while (true) {
        try {
            if (env->event_engine->is_core_empty()) {
                market_maker->update_market();
                _pending_order_checker->run();
            } else {
                op::EVENT cur_event = env->event_engine->get();
                _run_event_loop(cur_event);
            };

        } catch (BacktestFinished &e) {
            std::cout << e.what() << std::endl;
            break;
        };
    };
};

void OnePiece::initialize_trading_system() {
    _pre_initialize_trading_system();
    env->initialize_env();
    market_maker->initialize();
    env->recorder->initialize();
};

void OnePiece::_run_event_loop(const op::EVENT &event) {
    for (auto &single_loop : _event_loop) {
        if (_event_is_executed(event, single_loop))
            break;
    };
};

bool OnePiece::_event_is_executed(const op::EVENT &cur_event,
                                  op::SingleLoop &single_loop) const {

    if (cur_event == single_loop.if_event) {
        single_loop.run();
        if (single_loop.then_event != op::EVENT::None)
            env->event_engine->put(single_loop.then_event);
        return true;
    };
    return false;
};

void OnePiece::_pre_initialize_trading_system(){};

void OnePiece::set_date(const string &fromdate,
                        const string &todate,
                        const string &frequency) {
    env->fromdate = fromdate;
    env->todate = todate;
    env->sys_frequency = frequency;
};

void OnePiece::set_stock_backtest(const double initial_cash,
                                  const double comm,
                                  const double comm_pct,
                                  const double margin_rate) {
    env->instrument = "A_shares";
    StockBroker broker;
    StockRecorder recorder;
    env->recorder->set_setting(initial_cash, comm,
                               comm_pct, margin_rate);
};

void OnePiece::set_forex_backtest(const double initial_cash,
                                  const double margin_rate) {
    env->instrument = "Forex";
    ForexBroker broker;
    ForexRecorder recorder;
    env->recorder->set_setting(initial_cash, 0,
                               0, margin_rate);
};

OP_NAMESPACE_END


