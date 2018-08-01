#pragma once

#include "../sys_module/ReaderBase.h"
#include "../sys_module/models/OhlcClass.h"
#include <string>
#include <vector>

using std::shared_ptr;
using std::string;
using std::vector;

//class CsvOhlcClass : public OhlcClass {
//public:
//void set_value(const vector<string> &columns,
//const vector<string> &line_array); //覆盖虚函数
//};

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
    OhlcStruct _set_value(const vector<string> &columns,
                          const vector<string> &line_array); //覆盖虚函数
};
