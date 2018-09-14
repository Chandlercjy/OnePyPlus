#include "Environment.h"
#include "OnePieceWrapper.hpp"
#include "builtin_module/CsvReader.h"
#include "builtin_module/MongodbReader.h"
#include "strategy_wrapper.hpp"
#include <boost/python.hpp>
#include <boost/python/make_function.hpp>
#include <boost/python/overloads.hpp>
#include <boost/python/suite/indexing/map_indexing_suite.hpp>
#include <boost/python/suite/indexing/vector_indexing_suite.hpp>
#include <iostream>

using namespace op;

BOOST_PYTHON_MODULE(OnePyPlus) {
    using namespace op;
    using namespace boost::python;

    using StringList = vector<string>;
    class_<StringList>("StringList")
        .def(vector_indexing_suite<StringList>());

    using Dict_StrList = map<string, vector<string>>;
    class_<Dict_StrList>("Dict_StrList")
        .def(map_indexing_suite<Dict_StrList>());

    class_<Environment>("Environment")
        .add_property("instrument", &Environment::instrument)
        .add_property("sys_date", &Environment::sys_date)
        .add_property("sys_frequency", &Environment::sys_frequency)
        .add_property("fromdate", &Environment::fromdate)
        .add_property("todate", &Environment::todate)
        .add_property("tickers", &Environment::tickers)
        .add_property("cur_suspended_tickers", &Environment::cur_suspended_tickers)
        .add_property("suspended_tickers_record", &Environment::suspended_tickers_record)
        .add_property("recorder", &Environment::recorder);

    class_<CsvReader>("CsvReader", init<string, string, string>());
    class_<MongodbReader>("MongodbReader", init<string, string>());

    export_OnePiece();
    export_StrategyBase();

    //

    //def("get_env", &get_env, return_value_policy<reference_existing_object>());
}
