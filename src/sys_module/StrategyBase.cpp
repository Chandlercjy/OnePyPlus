#include "../Environment.h"
#include "StrategyBase.h"

namespace sys {

void StrategyBase::run(){};

template <typename strategy_name>
void StrategyBase::save_to_env(const strategy_name *self_ptr) {
    env->strategies["ss"] = std::make_shared<strategy_name>(*self_ptr); //TODO:设置名字
}
} // namespace sys
