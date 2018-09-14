#include "Environment.h"
#include "builtin_module/MongodbReader.h"
#include "utils/arrow.h"

#include <bsoncxx/builder/basic/document.hpp>
#include <bsoncxx/builder/basic/kvp.hpp>
#include <bsoncxx/builder/basic/sub_document.hpp>
#include <bsoncxx/json.hpp>
#include <bsoncxx/types.hpp>
#include <iostream>
#include <mongocxx/client.hpp>
#include <mongocxx/uri.hpp>

#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/json.hpp>

#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>

OP_NAMESPACE_START

using std::getline;
using std::ifstream;
using std::ios;
using std::stringstream;

using bsoncxx::builder::stream::close_document;
using bsoncxx::builder::stream::document;
using bsoncxx::builder::stream::finalize;
using bsoncxx::builder::stream::open_document;

MongodbReader::MongodbReader(const string &database,
                             const string &ticker)
    : ReaderBase(ticker),
      database(database) {
    auto module = make_shared<MongodbReader>(*this);
    env->save_module(ticker, module);
};

inline vector<string> seperate_key_value(stringstream &line_str) {
    vector<string> columns_array;
    string column;
    while (getline(line_str, column, '"')) {
        columns_array.push_back(column);
    };
    return columns_array;
}

inline vector<string> read_line(string &line_str) {
    stringstream columns(line_str);
    vector<string> columns_array = seperate_key_value(columns);
    return columns_array;
}

inline vector<string> seperate_str(stringstream &line_str) {
    vector<string> columns_array;
    string column;
    while (getline(line_str, column, ',')) {
        columns_array.push_back(column);
    };
    return columns_array;
}

inline const double remove_junk(const string &str) {
    return stod(str.substr(2, str.size() - 1));
};

inline OhlcVector::value_type settle_ohlc(const vector<string> &line_array) {
    string date;
    double open;
    double high;
    double low;
    double close;
    double volume;

    for (int i = 0; i < line_array.size(); i++) {
        const string value = line_array[i];

        if (value == "date") {
            date = line_array[i + 2];
        } else if (value == "open") {
            open = remove_junk(line_array[i + 1]);
        } else if (value == "high") {
            high = remove_junk(line_array[i + 1]);
        } else if (value == "low") {
            low = remove_junk(line_array[i + 1]);
        } else if (value == "close") {
            close = remove_junk(line_array[i + 1]);
        } else if (value == "volume") {
            volume = remove_junk(line_array[i + 1]);
        };
    };
    return OhlcVector::value_type(date, open, high, low, close, volume);
}


OhlcVectorPtr MongodbReader::load(const string &fromdate,
                                  const string &todate,
                                  const string &frequency) const {

    static mongocxx::instance inst{};
    static mongocxx::client connect{mongocxx::uri{}};

    auto bar_series = make_shared<OhlcVector>();

    auto collection = connect[database][frequency];

    //日期排好序
    auto date_order = document{} << "date" << 1 << finalize;
    auto opts = mongocxx::options::find{};
    opts.sort(date_order.view());

    auto cursor = collection.find(document{} << "date" << open_document
                                             << "$gte" << fromdate
                                             << "$lte" << todate
                                             << close_document << finalize,
                                  opts);

    for (auto &&doc : cursor) {
        //std::cout<<bsoncxx::to_json(doc);
        stringstream single_query(bsoncxx::to_json(doc));
        // 以引号为分界点
        vector<string> line_array = seperate_key_value(single_query);
        bar_series->emplace_back(settle_ohlc(line_array));
    }
    return bar_series;
}

OP_NAMESPACE_END
