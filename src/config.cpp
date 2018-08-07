#include "config.h"

namespace config {

template <class T>
inline void run_modules(T &modules) {
    for (auto &module : modules) {
        module.second->run();
    };
}

SingleLoop::SingleLoop(EVENT if_event, EVENT then_event,
                       string module_name)
    : if_event(if_event),
      then_event(then_event),
      _module_name(module_name) { _env = Environment::getInstance(); };

void SingleLoop::run() {
    if (_module_name == "cleaners")
        run_modules(_env->cleaners);
    else if (_module_name == "strategies")
        run_modules(_env->strategies);
    else if (_module_name == "riskmanagers")
        run_modules(_env->risk_managers);
    else if (_module_name == "brokers")
        run_modules(_env->brokers);
    else if (_module_name == "recorders")
        run_modules(_env->recorders);
}
} // namespace config
