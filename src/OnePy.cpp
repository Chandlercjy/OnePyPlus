#include "Constants.h"
#include "Environment.h"
#include "EventEngine.h"
#include "Exceptions.h"
#include "OnePy.h"
#include "config.h"
#include "sys_module//components/MarketMaker.h"
#include "sys_module//components/PendingOrderChecker.h"
#include "sys_module/RecorderBase.h"
#include <iostream>

OP_NAMESPACE_START
using std::make_shared;
using std::shared_ptr;

OnePiece::OnePiece()
    : env(op::Environment::get_instance()),
      market_maker(make_shared<op::MarketMaker>()),
      _event_loop(op::EVENT_LOOP),
      _pending_order_checker(make_shared<op::PendingOrderChecker>()){};

void OnePiece::sunny(const bool &show_summary) {
    initialize_trading_system();
    while (true) {
        try {
            if (!env->event_engine->is_core_empty()) {
                op::EVENT cur_event = env->event_engine->get();
                _run_event_loop(cur_event);
            } else {
                market_maker->update_market();
                _pending_order_checker->run();
            };

        } catch (except::BacktestFinished &e) {
            std::cout << e.what() << std::endl;
            if (show_summary)
                output_summary();
            break;
        } catch (except::QueueEmptyError &e) {
            std::cout << e.what() << std::endl; // Hope Never Raised!
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
                        const string &frequency,
                        const string &instrument) {
    env->instrument = instrument;
    env->fromdate = fromdate;
    env->todate = todate;
    env->sys_frequency = frequency;
};

OP_NAMESPACE_END
