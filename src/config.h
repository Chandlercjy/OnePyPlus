#pragma once
#include <vector>

// 控制事件发生顺序

namespace sys {

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

typedef std::vector<SingleLoop> LoopVector;
extern LoopVector EVENT_LOOP;

template <class T>
inline void run_modules();
}; // namespace sys
