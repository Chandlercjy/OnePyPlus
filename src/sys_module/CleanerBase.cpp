#include "../Environment.h"
#include "CleanerBase.h"

namespace sys {

CleanerBase::CleanerBase()
    : env(Environment::get_instance()){};

void CleanerBase::run() {
    ;
};

void CleanerBase::initialize_buffer_data(const string &ticker, int &bufferday){};

template <typename cleaner_name>
void CleanerBase::save_to_env(const cleaner_name *self_ptr) {
    env->cleaners["s"] = std::make_shared<cleaner_name>(*self_ptr); //TODO:写名字
}
} // namespace sys
