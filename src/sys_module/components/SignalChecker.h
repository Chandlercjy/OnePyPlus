
#include "OP_DECLARE.h"

#pragma once

OP_NAMESPACE_START

class SignalChecker {
  public:
    void check_conflict(const double obj,
                        const double obj_pct,
                        const string &name);
    void check_size(const int size);

    void save_signals(const int size);
};

OP_NAMESPACE_END
