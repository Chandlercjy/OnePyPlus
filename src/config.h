#pragma once
#include "constants.h"
#include "environment.h"
#include <map>
#include <vector>

// 控制事件发生顺序

namespace config {

struct SingleLoop;
typedef std::vector<SingleLoop> LoopVector;

struct SingleLoop {
    SingleLoop(EVENT if_event, EVENT then_event, MODULES module_name);
    const EVENT if_event;
    const EVENT then_event;
    void run();

  private:
    MODULES _module_name;
    const Environment *_env;
};

extern LoopVector EVENT_LOOP;
}; // namespace config
