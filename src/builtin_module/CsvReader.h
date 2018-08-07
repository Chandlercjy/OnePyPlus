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

class CsvReader : public ReaderBase {
  public:
    CsvReader(const string &data_path, const string &ticker)
        : ticker(ticker) { _load_raw_data(data_path); };

    const string ticker;
    OhlcVector bar_series;
    OhlcVector::iterator load(const string &fromdate,
                              const string &todate,
                              const string &frequency) override;

  private:
    void _load_raw_data(const string &data_path);
    inline void _check_is_file_exist(const ifstream &file,
                                     const string &data_path);
    OhlcVector::value_type _set_value(const vector<string> &columns,
                                      const vector<string> &line_array); //覆盖虚函数
};
} // namespace sys
