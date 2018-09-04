#include "OP_DECLARE.h"
#include "sys_module/ReaderBase.h"
#include <fstream>
#include <iostream>
#include <sstream>

#pragma once

OP_NAMESPACE_START

using std::ifstream;

class CsvReader : public ReaderBase {
  public:
    CsvReader(const string &data_path,
              const string &file_name,
              const string &ticker);

    shared_ptr<OhlcVector> load(const string &fromdate,
                                const string &todate,
                                const string &frequency) const override;

    const string file_name;
    const string data_path;
};
OP_NAMESPACE_END
