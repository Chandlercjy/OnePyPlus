#include "EventEngine.cpp"
#include "Exceptions.h"
#include "OnePy.h"
#include "builtin_module/CsvReader.cpp"
#include "config.cpp"
#include "constants.h"
#include "environment.cpp"
#include "sys_module/BrokerBase.cpp"
#include "sys_module/CleanerBase.cpp"
#include "sys_module/ReaderBase.cpp"
#include "sys_module/RecorderBase.cpp"
#include "sys_module/RiskManagerBase.cpp"
#include "sys_module/StrategyBase.cpp"
#include "sys_module/models/BarBase.cpp"
#include "utils.cpp"

void OnePiece::sunny(const bool &show_summary) {
    _pre_initialize_trading_system();
    initialize_trading_system();
    //order_checker = PendingOrderChecker();
    int a = 1;
    while (a < 8) {
        a++;

        try {
            if (!env->event_bus.is_core_empty()) {
                EVENT cur_event = env->event_bus.get();
                _run_event_loop(cur_event);
                print(cur_event);
            } else {
                //self.env.market_maker.update_market();
                //order_checker.run();
            };

        } catch (except::BacktestFinished &e) {
            e.what();
            if (show_summary)
                output_summary();
            break;
        } catch (except::QueueEmptyError &e) {
            e.what(); // Hope Never Raised!
            break;
        };
    };
};

void OnePiece::initialize_trading_system(){};

void OnePiece::_run_event_loop(const EVENT &event) {
    for (auto &single_loop : config::EVENT_LOOP) {
        if (_event_is_executed(event, single_loop))
            break;
    };
};

bool OnePiece::_event_is_executed(const EVENT &cur_event,
                                  config::SingleLoop &single_loop) {

    if (cur_event == single_loop.if_event) {
        single_loop.run();
        if (single_loop.then_event != EVENT::None)
            env->event_bus.put(single_loop.then_event);
        return true;
    };
    return false;
};

void OnePiece::_reset_all_counter(){};
void OnePiece::_pre_initialize_trading_system(){};
