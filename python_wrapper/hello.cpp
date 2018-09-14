#include "Constants.h"
#include "Environment.h"
#include "EventEngine.h"
#include "ExceptionWrapper.hpp"
#include "OnePy.h"
#include "builtin_module/CsvReader.h"
#include "builtin_module/backtest_stock/StockBroker.h"
#include "builtin_module/backtest_stock/StockRecorder.h"
#include "builtin_module/backtest_stock/StockSeries.h"
#include "custom_module/backtest.h"
#include "strategy_wrapper.hpp"
#include "sys_module/components/MarketMaker.h"
#include "sys_module/components/PendingOrderChecker.h"
#include "sys_module/models/SeriesBase.h"
#include <boost/python.hpp>
#include <exception>
#include <iostream>

using namespace op;

class OnePieceWrapper {

  public:
    Environment *env = Environment::get_instance();
    void sunny(const bool show_summary = true) { go.sunny(show_summary); };

    void set_date(const string &fromdate,
                  const string &todate,
                  const string &frequency,
                  const string &instrument) {
        go.set_date(fromdate, todate, frequency, instrument);
    };

    void set_stock_backtest(const double initial_cash,
                            const double comm,
                            const double comm_pct,
                            const double margin_rate) {
        go.set_stock_backtest(initial_cash, comm, comm_pct, margin_rate);
    };

    py::list balance() {
        static auto result = _get_money_series(env->recorder->balance->data);
        return result;
    };
    py::list cash() {
        static auto result = _get_money_series(env->recorder->cash->data);
        return result;
    };
    py::list frozen_cash() {
        static auto result = _get_money_series(env->recorder->frozen_cash->data);
        return result;
    };
    py::dict holding_pnl() {
        static auto result = _get_money_series(env->recorder->holding_pnl->data);
        return result;
    };
    py::dict realized_pnl() {
        static auto result = _get_money_series(env->recorder->realized_pnl->data);
        return result;
    };
    py::dict commission() {
        static auto result = _get_money_series(env->recorder->commission->data);
        return result;
    };
    py::dict position() {
        static auto result = _get_money_series(env->recorder->position->data);
        return result;
    };
    py::dict margin() {
        static auto result = _get_money_series(env->recorder->margin->data);
        return result;
    };
    py::dict avg_price() {
        static auto result = _get_money_series(env->recorder->avg_price->data);
        return result;
    };

  private:
    OnePiece go;

    py::list _get_money_series(vector<SeriesStruct> &series) {
        py::list result;
        for (auto &obj : series) {
            py::dict temp_dict;
            temp_dict["date"] = obj.date;
            temp_dict["value"] = obj.value;
            result.append(temp_dict);
        }
        return result;
    };

    py::dict _get_money_series(map<string, vector<SeriesStruct>> &series) {
        py::dict result;
        for (auto &key_value : series) {
            py::list temp_list;
            for (auto &obj : key_value.second) {
                py::dict temp_dict;
                temp_dict["date"] = obj.date;
                temp_dict["value"] = obj.value;
                temp_list.append(temp_dict);
            }
            result[key_value.first] = temp_list;
        }
        return result;
    };
};

#include <boost/python/make_function.hpp>
#include <boost/python/overloads.hpp>
#include <boost/python/suite/indexing/map_indexing_suite.hpp>
#include <boost/python/suite/indexing/vector_indexing_suite.hpp>

BOOST_PYTHON_MODULE(OnePyPlus) {
    using namespace op;
    using namespace boost::python;

    using StringList = vector<string>;
    class_<StringList>("StringList")
        .def(vector_indexing_suite<StringList>());

    using Dict_StrList = map<string, vector<string>>;
    class_<Dict_StrList>("Dict_StrList")
        .def(map_indexing_suite<Dict_StrList>());

    class_<CsvReader>("CsvReader", init<string, string, string>());
    class_<Environment>("Environment")
        .add_property("instrument", &Environment::instrument)
        .add_property("sys_date", &Environment::sys_date)
        .add_property("sys_frequency", &Environment::sys_frequency)
        .add_property("fromdate", &Environment::fromdate)
        .add_property("todate", &Environment::todate)
        .add_property("tickers", &Environment::tickers)
        .add_property("cur_suspended_tickers", &Environment::cur_suspended_tickers)
        .add_property("suspended_tickers_record", &Environment::suspended_tickers_record)
        .add_property("recorder", &Environment::recorder)

        ;

    class_<OnePieceWrapper>("OnePiece")
        .def("sunny", &OnePieceWrapper::sunny)
        .def("set_date", &OnePieceWrapper::set_date)
        .def("set_stock_backtest", &OnePieceWrapper::set_stock_backtest)
        .add_property("balance", &OnePieceWrapper::balance)
        .add_property("cash", &OnePieceWrapper::cash)
        .add_property("frozen_cash", &OnePieceWrapper::frozen_cash)
        .add_property("holding_pnl", &OnePieceWrapper::holding_pnl)
        .add_property("realized_pnl", &OnePieceWrapper::realized_pnl)
        .add_property("commission", &OnePieceWrapper::commission)
        .add_property("position", &OnePieceWrapper::position)
        .add_property("avg_price", &OnePieceWrapper::avg_price);

    export_StrategyBase();

    //

    //def("get_env", &get_env, return_value_policy<reference_existing_object>());
}
