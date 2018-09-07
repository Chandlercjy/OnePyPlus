#include "Environment.h"
#include "sys_module/ReaderBase.h"

OP_NAMESPACE_START

ReaderBase::ReaderBase(const string &ticker)
    : env(Environment::get_instance()),
      ticker(ticker){};

shared_ptr<OhlcVector> ReaderBase::load_by_cleaner(const string &fromdate,
                                                   const string &todate,
                                                   const string &frequency) {
    return load(fromdate, todate, frequency);
};

OP_NAMESPACE_END
