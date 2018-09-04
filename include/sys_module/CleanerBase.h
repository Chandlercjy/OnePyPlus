#include "OP_DECLARE.h"

#pragma once

OP_NAMESPACE_START

class Environment;

class CleanerBase {

  public:
    CleanerBase();

    Environment *env;

    int bufferday;

    void run();
    virtual ~CleanerBase() = default;

    void initialize_buffer_data(const string &ticker, int &bufferday);

  protected:
    template <typename T>
    void save_to_env(const T *self_ptr, const string &name);
};

OP_NAMESPACE_END
