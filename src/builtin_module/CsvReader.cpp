#include "CsvReader.h"

namespace sys {

using std::ifstream;
using std::ios;
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
    if (!file)
        std::cout << data_path << " 不存在!!可能路径不正确" << std::endl;
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

void CsvReader::_load_raw_data(const string &data_path) {
    ifstream in_file(data_path, ios::in);
    check_is_file_exist(in_file, data_path); // 判断文件是否存在

    string line_str;
    getline(in_file, line_str); // read columns
    auto columns_array = read_line(line_str);

    while (getline(in_file, line_str)) { //read data
        auto line_array = read_line(line_str);
        bar_series.push_back(settle_ohlc(columns_array, line_array));
    };
}

OhlcVector::const_iterator CsvReader::load(const string &fromdate,
                                           const string &todate,
                                           const string &frequency) {
    return bar_series.begin();
}
} // namespace sys
