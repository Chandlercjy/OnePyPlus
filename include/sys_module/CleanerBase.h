#include "OP_DECLARE.h"

#pragma once

OP_NAMESPACE_START

class Environment;

class CleanerBase {

  public:
    CleanerBase();
    virtual ~CleanerBase() = default;

    Environment *env;

    int bufferday;

    void run();

    void initialize_buffer_data(const string &ticker, int &bufferday);
};

OP_NAMESPACE_END
