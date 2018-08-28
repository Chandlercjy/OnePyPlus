#include "Constants.h"
#include "Environment.h"
#include "EventEngine.h"
#include "Exceptions.h"
#include "OnePy.h"
#include "config.h"
#include "sys_module//components/MarketMaker.h"

namespace op {

OnePiece::OnePiece()
    : env(sys::Environment::get_instance()),
      _market_maker(std::make_unique<MarketMaker>()){};

void OnePiece::sunny(const bool &show_summary) {
    initialize_trading_system();
    //order_checker = PendingOrderChecker();
    while (true) {
        try {
            if (!env->event_engine->is_core_empty()) {
                sys::EVENT cur_event = env->event_engine->get();
                _run_event_loop(cur_event);
            } else {
                _market_maker->update_market();
                //order_checker.run();
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

void OnePiece::_run_event_loop(const sys::EVENT &event) const {
    for (auto &single_loop : sys::EVENT_LOOP) {
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

void OnePiece::_reset_all_counter() const {};
void OnePiece::_pre_initialize_trading_system(){};

} // namespace op
