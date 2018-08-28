#include "../Environment.h"
#include "RiskManagerBase.h"

namespace sys {

RiskManagerBase::RiskManagerBase()
    : env(Environment::get_instance()){};

void RiskManagerBase::run(){};

template <typename risk_manager_name>
void RiskManagerBase::save_to_env(const risk_manager_name *self_ptr) {
    env->risk_managers[get_name()] = std::make_shared<risk_manager_name>(*self_ptr); //TODO:设置名字
}
} // namespace sys
