#include "../Environment.h"
#include "RecorderBase.h"

namespace sys {

RecorderBase::RecorderBase() : env(Environment::get_instance()){};
void RecorderBase::initialize(){};
void RecorderBase::run(){};
void RecorderBase::update(const bool &order_executed){

};

template <typename recorder_name>
void RecorderBase::save_to_env(const recorder_name *self_ptr) {
    env->recorders["ss"] = std::make_shared<recorder_name>(*self_ptr); //TODO:设置名字
    env->recorder = env->recorders["ss"];
}
} // namespace sys
