#include "RiskManagerBase.h"
#include "../Environment.h"

namespace sys {
void RiskManagerBase::run(){};

template <typename risk_manager_name>
void RiskManagerBase::save_to_env(const risk_manager_name *self_ptr) {
    env->risk_managers["ss"] = std::make_shared<risk_manager_name>(*self_ptr); //TODO:设置名字
}
} // namespace sys
