#include "Environment.h"
#include "sys_module/CleanerBase.h"

OP_NAMESPACE_START

CleanerBase::CleanerBase()
    : env(Environment::get_instance()){};

void CleanerBase::run(){};

void CleanerBase::initialize_buffer_data(const string &ticker, int &bufferday){};

OP_NAMESPACE_END
