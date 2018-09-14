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
#include "sys_module/components/MarketMaker.h"
#include "sys_module/components/PendingOrderChecker.h"
#include <boost/python.hpp>
#include <exception>
#include <iostream>
#include "strategy_wrapper.hpp"

using namespace op;
using namespace boost::python;

//class StrategyBasePy : public StrategyBase {
//public:
//const string name;
//StrategyBasePy(const string &name)
//: name(name){};

//void save_module(StrategyBasePy *strategy) {
//auto module = std::make_shared<StrategyBasePy>(*strategy);
//env->save_module(name, module);
//};

//void print_balance() {
//std::cout << env->recorder->balance->latest()
//<< ", "
//<< env->sys_date
//<< std::endl;
//};

//void print_position() {
//std::cout << env->recorder->position->latest("000001", "long")
//<< ", "
//<< env->sys_date
//<< std::endl;
//};

//virtual void handle_bar() override {
////std::cout<<4;
////buy(20, "000001", 0, 0, 0, 0, 0, 0, 0, 0.01);
////buy(10, "000001");
//std::cout << env->recorder->balance->latest()
//<< ", "
//<< env->sys_date
//<< std::endl;
//};
//};

//class Luffy : public StrategyBase {
//public:
//Luffy() {
//auto module = std::make_shared<Luffy>(*this);
//env->save_module("Luffy", module);
//};
//void handle_bar() override {
////buy(20, "000001", 0, 0, 0, 0, 0, 0, 0, 0.01);
//buy(10, "000001");
//std::cout << env->recorder->balance->latest()
//<< ", "
//<< env->sys_date
//<< std::endl;
//};
//};

class OnePiecePy {
  public:
    void set_date(const string &fromdate,
                  const string &todate,
                  const string &frequency,
                  const string &instrument) {
        go.set_date(fromdate, todate, frequency, instrument);
        ;
    };

    void set_stock_backtest(const double initial_cash,
                            const double comm,
                            const double comm_pct,
                            const double margin_rate) {
        StockBroker broker;
        StockRecorder recorder;
        go.env->recorder->set_setting(initial_cash, comm,
                                      comm_pct, margin_rate);
    };

    void _cpp_initialize_trading_system() {
        go.initialize_trading_system();
    };

    bool _cpp_event_engine_is_empty() {
        return go.env->event_engine->is_core_empty();
    };
    void _cpp_market_maker_update_market() {
        go.market_maker->update_market();
    };
    void _cpp_pending_order_checker_run() {
        go._pending_order_checker->run();
    };

    //self._cpp_run_event_loop(cur_event)
    string _cpp_get_cur_event() {
        if (go.env->event_engine->get() == EVENT::Market_updated)
            return "Market_updated";
        throw std::logic_error("Never Raised");
        return "";
    };

    void _cpp_run_brokers() {
        for (auto &broker : go.env->brokers)
            broker.second->run();
    };
    void _cpp_run_recorders() {
        for (auto &recorder : go.env->recorders)
            recorder.second->run();
    };

  private:
    OnePiece go;
};


void print_balance() {
    static Environment *env = Environment::get_instance();
    std::cout << env->recorder->balance->latest()
              << ", "
              << env->sys_date
              << std::endl;
};
    //void load_csv_reader(const string &data_path,
    //const string &file_name,
    //const string &ticker) {
    //CsvReader new_csv_reader(data_path, file_name, ticker);
    //};
    //

#include <boost/python/make_function.hpp>
#include <boost/python/overloads.hpp>
#include <boost/python/suite/indexing/map_indexing_suite.hpp>
#include <boost/python/suite/indexing/vector_indexing_suite.hpp>


BOOST_PYTHON_MODULE(OnePyPlus) {
    using namespace op;

    //register_exception_translator<BacktestFinished>(translateBacktestFinished);

    //def("someFunction", &someFunction);

    //class_<OnePiecePy>("OnePiece")
    //.def("set_date", &OnePiecePy::set_date)
    //.def("set_stock_backtest", &OnePiecePy::set_stock_backtest)
    //.def("_cpp_event_engine_is_empty", &OnePiecePy::_cpp_event_engine_is_empty)
    //.def("_cpp_get_cur_event", &OnePiecePy::_cpp_get_cur_event)
    //.def("_cpp_initialize_trading_system", &OnePiecePy::_cpp_initialize_trading_system)
    //.def("_cpp_market_maker_update_market", &OnePiecePy::_cpp_market_maker_update_market)
    //.def("_cpp_pending_order_checker_run", &OnePiecePy::_cpp_pending_order_checker_run)
    //.def("_cpp_run_brokers", &OnePiecePy::_cpp_run_brokers)
    //.def("_cpp_run_recorders", &OnePiecePy::_cpp_run_recorders)
    //.def("_cpp_initialize_trading_system", &OnePiecePy::_cpp_initialize_trading_system);

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
        .add_property("suspended_tickers_record", &Environment::suspended_tickers_record);

    class_<OnePiece>("OnePiece")
        .def("sunny", &OnePiece::sunny)
        .def("set_date", &OnePiece::set_date)
        .def("set_stock_backtest", &OnePiece::set_stock_backtest);

    export_StrategyBase();

    def("print_balance", &print_balance);
    //def("get_env", &get_env, return_value_policy<reference_existing_object>());
}
