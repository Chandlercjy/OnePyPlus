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
      module_name(module_name) { env = Environment::getInstance(); };

void SingleLoop::run() {
    if (module_name == "cleaners")
        run_modules(env->cleaners);
    else if (module_name == "strategies")
        run_modules(env->strategies);
    else if (module_name == "riskmanagers")
        run_modules(env->risk_managers);
    else if (module_name == "brokers")
        run_modules(env->brokers);
    else if (module_name == "recorders")
        run_modules(env->recorders);
}
} // namespace config
