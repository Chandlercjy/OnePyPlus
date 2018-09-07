#include "Environment.h"
#include "sys_module/RiskManagerBase.h"

OP_NAMESPACE_START

RiskManagerBase::RiskManagerBase()
    : env(Environment::get_instance()){};

void RiskManagerBase::run(){};

OP_NAMESPACE_END
