#include "EventEngine.cpp"
#include "Exceptions.h"
#include "OnePy.h"
#include "builtin_module/CsvReader.cpp"
#include "config.h"
#include "constants.h"
#include "environment.cpp"
#include "utils.h"

void print_finished() {
    cout << "hhhhh" << endl;
    throw 'f';
}

void OnePiece::sunny(const bool &show_summary) {
    _pre_initialize_trading_system();
    initialize_trading_system();
    //order_checker = PendingOrderChecker();
    int a = 1;
    while (a < 8) {
        a++;

        try {
            if (!this->env->event_bus.is_core_empty()) {
                EVENT cur_event = this->env->event_bus.get();
                this->_run_event_loop(cur_event);
                print_type(cur_event);
            } else {
                //self.env.market_maker.update_market();
                //order_checker.run();
            };

        } catch (except::BacktestFinished &e) {
            e.what();
            if (show_summary)
                this->output_summary();
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
        if (this->_event_is_executed(event, single_loop))
            break;
    };
};

bool OnePiece::_event_is_executed(const EVENT &cur_event,
                                  const config::SingleLoop &single_loop) {
    if (cur_event == single_loop.if_event) {
        for (auto &module : *single_loop.module_dict) {
            module.second->run();
        };
        if (single_loop.then_event != EVENT::None)
            this->env->event_bus.put(single_loop.then_event);
        return true;
    };
    return false;
};

void OnePiece::_reset_all_counter(){};
void OnePiece::_pre_initialize_trading_system(){};
