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
    CsvReader(const string &data_path, const string &ticker)
        : ReaderBase(ticker) { _load_raw_data(data_path); };

    OhlcVector bar_series;
    OhlcVector::iterator load(const string &fromdate,
                              const string &todate,
                              const string &frequency) override;

  private:
    void _load_raw_data(const string &data_path);
};
} // namespace sys
