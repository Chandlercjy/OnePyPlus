#include "OP_DECLARE.h"
#include "sys_module/ReaderBase.h"

#pragma once

OP_NAMESPACE_START

class MongodbReader : public ReaderBase {
  public:
    MongodbReader(const string &database,
                  const string &ticker);

    const string database;

    OhlcVectorPtr load(const string &fromdate,
                       const string &todate,
                       const string &frequency) const override;
};

OP_NAMESPACE_END
