#include "../Environment.h"
#include "RecorderBase.h"

namespace sys {

void RecorderBase::run(){};

template <typename recorder_name>
void RecorderBase::save_to_env(const recorder_name *self_ptr) {
    env->recorders["ss"] = make_shared<recorder_name>(*self_ptr); //TODO:设置名字
}
} // namespace sys
