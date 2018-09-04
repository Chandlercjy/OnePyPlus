#include "Environment.h"
#include "sys_module/CleanerBase.h"

OP_NAMESPACE_START

CleanerBase::CleanerBase()
    : env(Environment::get_instance()){};

void CleanerBase::run(){};

void CleanerBase::initialize_buffer_data(const string &ticker, int &bufferday){};

template <typename T>
void CleanerBase::save_to_env(const T *self_ptr, const string &name) {
    env->cleaners[name] = make_shared<T>(*self_ptr); //TODO:写名字
}

OP_NAMESPACE_END

