#include "Environment.h"
#include "config.h"
#include "constants.h"

namespace sys {

template <class T>
void run_modules(T &modules) {
    for (auto &module : *modules) {
        module.second->run();
    };
}

SingleLoop::SingleLoop(EVENT if_event, EVENT then_event,
                       MODULES module_name)
    : if_event(if_event),
      then_event(then_event),
      _module_name(module_name),
      _env(Environment::get_instance()){};

void SingleLoop::run() {
    switch (_module_name) {
        case MODULES::Cleaners:
            run_modules(_env->cleaners);
            break;
        case MODULES::Strategies:
            run_modules(_env->strategies);
            break;
        case MODULES::Risk_managers:
            run_modules(_env->risk_managers);
            break;
        case MODULES::Brokers:
            run_modules(_env->brokers);
            break;
        case MODULES::Recorders:
            run_modules(_env->recorders);
            break;
    };
}

LoopVector EVENT_LOOP = {SingleLoop(EVENT::Market_updated,
                                    EVENT::Data_cleaned,
                                    MODULES::Cleaners),

                         SingleLoop(EVENT::Data_cleaned,
                                    EVENT::Signal_generated,
                                    MODULES::Strategies),

                         SingleLoop(EVENT::Signal_generated,
                                    EVENT::Submit_order,
                                    MODULES::Risk_managers),

                         SingleLoop(EVENT::Submit_order,
                                    EVENT::Record_result,
                                    MODULES::Brokers),

                         SingleLoop(EVENT::Record_result,
                                    EVENT::None,
                                    MODULES::Recorders)};
} // namespace sys
