#include "Environment.h"
#include "sys_module/RiskManagerBase.h"

OP_NAMESPACE_START

RiskManagerBase::RiskManagerBase()
    : env(Environment::get_instance()){};

void RiskManagerBase::run(){};

template <typename T>
void RiskManagerBase::save_to_env(const T *self_ptr, const string &name) {
    env->risk_managers[name] = make_shared<T>(*self_ptr); //TODO:设置名字
}
OP_NAMESPACE_END


