#include "CsvReader.h"

namespace sys {
using std::ifstream;
using std::ios;
using std::string;
using std::stringstream;
using std::vector;

OhlcVector::value_type CsvReader::_set_value(const vector<string> &columns,
                                             const vector<string> &line_array) {
    const int count = columns.size();
    string date;
    double open;
    double high;
    double low;
    double close;
    double volume;

    for (int i = 0; i < count; i++) {

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
};

inline void CsvReader::_check_is_file_exist(const ifstream &file,
                                            const string &data_path) {
    if (!file)
        std::cout << data_path << " 不存在!!可能路径不正确" << std::endl;
};

void CsvReader::_load_raw_data(const string &data_path) {

    ifstream in_file(data_path, ios::in);
    // 判断文件是否存在
    _check_is_file_exist(in_file, data_path);

    //read columns
    string line_str;
    getline(in_file, line_str);
    stringstream columns(line_str);
    vector<string> columns_array;
    string column;
    while (getline(columns, column, ',')) {
        columns_array.push_back(column);
    };

    //read data
    while (getline(in_file, line_str)) {
        stringstream value_str(line_str);
        string str;
        vector<string> line_array;

        while (getline(value_str, str, ','))
            line_array.push_back(str);

        auto single_bar = _set_value(columns_array, line_array);

        bar_series.push_back(single_bar);
    };
};

OhlcVector::iterator CsvReader::load(const string &fromdate,
                                     const string &todate,
                                     const string &frequency) {
    return bar_series.begin();
};
} // namespace sys
