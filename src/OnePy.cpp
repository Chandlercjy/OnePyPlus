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

namespace op {
using std::make_shared;
using std::shared_ptr;

OnePiece::OnePiece()
    : env(sys::Environment::get_instance()),
      _event_loop(sys::EVENT_LOOP),
      _market_maker(make_shared<sys::MarketMaker>()),
      _pending_order_checker(make_shared<sys::PendingOrderChecker>()){};

void OnePiece::sunny(const bool &show_summary) {
    initialize_trading_system();
    while (true) {
        try {
            if (!env->event_engine->is_core_empty()) {
                sys::EVENT cur_event = env->event_engine->get();
                _run_event_loop(cur_event);
            } else {
                _market_maker->update_market();
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
    _market_maker->initialize();
    env->recorder->initialize();
};

void OnePiece::_run_event_loop(const sys::EVENT &event) {
    for (auto &single_loop : _event_loop) {
        if (_event_is_executed(event, single_loop))
            break;
    };
};

bool OnePiece::_event_is_executed(const sys::EVENT &cur_event,
                                  sys::SingleLoop &single_loop) const {

    if (cur_event == single_loop.if_event) {
        single_loop.run();
        if (single_loop.then_event != sys::EVENT::None)
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

} // namespace op
