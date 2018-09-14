#include "DataType.h"
#include "OP_DECLARE.h"

#pragma once

OP_NAMESPACE_START

class Environment;

class ReaderBase {
  public:
    ReaderBase(const string &ticker);
    virtual ~ReaderBase() = default;

    Environment *env;
    const string ticker;

    virtual OhlcVectorPtr load(const string &fromdate,
                                        const string &todate,
                                        const string &frequency) const = 0;

    OhlcVectorPtr load_by_cleaner(const string &fromdate,
                                           const string &todate,
                                           const string &frequency);

};

OP_NAMESPACE_END
