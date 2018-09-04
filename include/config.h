#include "OP_DECLARE.h"

#pragma once

// 控制事件发生顺序

OP_NAMESPACE_START

using std::vector;

enum class EVENT;
enum class MODULES;
class Environment;

struct SingleLoop {
    SingleLoop(EVENT if_event,
               EVENT then_event,
               MODULES module_name);
    const EVENT if_event;
    const EVENT then_event;
    void run();

  private:
    MODULES _module_name;
    Environment *_env;
};

extern vector<SingleLoop> EVENT_LOOP;

template <typename T>
void run_modules();

OP_NAMESPACE_END
