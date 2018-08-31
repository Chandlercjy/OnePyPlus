#pragma once

#include "../sys_module/ReaderBase.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

namespace sys {
using std::ifstream;
using std::string;
using std::vector;

class CsvReader : public ReaderBase {
  public:
    CsvReader(const string &data_path, const string &file_name, const string &ticker);

    std::shared_ptr<OhlcVector> load(const string &fromdate,
                                     const string &todate,
                                     const string &frequency) const override;

    const string file_name;
    const string data_path;
};
} // namespace sys
