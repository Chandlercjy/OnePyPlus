#include "../Environment.h"
#include "BrokerBase.h"

namespace sys {
void BrokerBase::run(){};

template <typename broker_name>
void BrokerBase::save_to_env(const broker_name *self_ptr) {
    env->brokers["ss"] = std::make_shared<broker_name>(*self_ptr); //TODO:设置名字
}
} // namespace sys
