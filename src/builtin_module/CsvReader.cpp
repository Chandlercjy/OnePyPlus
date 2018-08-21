#include "../Environment.h"
#include "../Exceptions.h"
#include "../utils/arrow.h"
#include "../utils/utils.h"
#include "CsvReader.h"

namespace sys {

using namespace utils;
using std::ifstream;
using std::ios;
using std::shared_ptr;
using std::string;
using std::stringstream;
using std::vector;

inline OhlcVector::value_type settle_ohlc(const vector<string> &columns,
                                          const vector<string> &line_array) {
    string date;
    double open;
    double high;
    double low;
    double close;
    double volume;

    for (int i = 0; i < columns.size(); i++) {

        string key = columns[i];
        transform(key.begin(), key.end(), key.begin(), tolower); // 转化为小写

        const string str_value = line_array[i];
        if (key == "date") {
            date = str_value;
        } else {
            const double d_value = stod(line_array[i]); // string转化为double

            if (key == "open") {
                open = d_value;
            } else if (key == "high") {
                high = d_value;
            } else if (key == "low") {
                low = d_value;
            } else if (key == "close") {
                close = d_value;
            } else if (key == "volume") {
                volume = d_value;
            };
        };
    };
    return OhlcVector::value_type(date, open, high, low, close, volume);
}

inline void check_is_file_exist(const ifstream &file,
                                const string &data_path) {
    if (!file) {
        std::cout << data_path << " 不存在!!可能路径不正确" << std::endl;
        throw except::BacktestFinished();
    }
}

inline vector<string> seperate_str(stringstream &line_str) {
    vector<string> columns_array;
    string column;
    while (getline(line_str, column, ',')) {
        columns_array.push_back(column);
    };
    return columns_array;
}

inline vector<string> read_line(string &line_str) {
    stringstream columns(line_str);
    vector<string> columns_array = seperate_str(columns);
    return columns_array;
}

shared_ptr<OhlcVector> load_raw_data(const string &data_path,
                                     const string &file_name,
                                     const string &frequency) {
    string true_data_path = data_path + file_name + "_" + frequency + ".csv";

    auto bar_series = std::make_shared<OhlcVector>();
    ifstream in_file(true_data_path, ios::in);
    check_is_file_exist(in_file, true_data_path); // 判断文件是否存在

    string line_str;
    getline(in_file, line_str); // read columns
    auto columns_array = read_line(line_str);

    while (getline(in_file, line_str)) { //read data
        auto line_array = read_line(line_str);
        bar_series->push_back(settle_ohlc(columns_array, line_array));
    };
    return bar_series;
}

CsvReader::CsvReader(const string &data_path,
                     const string &file_name,
                     const string &ticker)
    : ReaderBase(ticker),
      file_name(file_name),
      data_path(data_path) { save_to_env(this); };

shared_ptr<OhlcVector> CsvReader::load(const string &fromdate,
                                       const string &todate,
                                       const string &frequency) const {
    shared_ptr<OhlcVector> bar_series = load_raw_data(data_path,
                                                      file_name,
                                                      frequency);
    shared_ptr<OhlcVector> result = std::make_shared<OhlcVector>();

    for (auto &bar : *bar_series) {
        if (arrow::is_gt(bar.date, todate))
            break;
        if (arrow::is_gte(bar.date, fromdate)) {
            result->push_back(bar);
        }
    };
    return result;
}
} // namespace sys
