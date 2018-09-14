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

    virtual shared_ptr<OhlcVector> load(const string &fromdate,
                                        const string &todate,
                                        const string &frequency) const = 0;

    shared_ptr<OhlcVector> load_by_cleaner(const string &fromdate,
                                           const string &todate,
                                           const string &frequency);

    //private:
    //_check_readers_key();
};

OP_NAMESPACE_END
