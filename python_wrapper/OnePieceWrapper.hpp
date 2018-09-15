#include "OnePy.h"
#include "builtin_module/backtest_stock/StockBroker.h"
#include "builtin_module/backtest_stock/StockRecorder.h"
#include "custom_module/backtest.h"
#include "strategy_wrapper.hpp"
#include "sys_module/components/MarketMaker.h"
#include "sys_module/components/MatchEngine.h"
#include "sys_module/components/PendingOrderChecker.h"
#include "sys_module/models/SeriesBase.h"
#include <boost/python.hpp>
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

    py::list tickers() {
        return py::list(env->tickers);
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

    py::dict trade_log() {
        auto &match_engine = env->recorder->match_engine;
        if (!match_engine->left_trade_settled) {
            match_engine->append_left_trade_to_log();
            match_engine->left_trade_settled = true;
        }
        py::dict log_dict;
        map<string, py::list> log_list;
        for (auto &log : match_engine->finished_log) {
            log_list["ticker"].append(log->ticker);
            log_list["entry_date"].append(log->entry_date);
            log_list["entry_price"].append(log->entry_price);
            log_list["entry_type"].append(log->entry_type);
            log_list["size"].append(log->size);
            log_list["exit_date"].append(log->exit_date);
            log_list["exit_price"].append(log->exit_price);
            log_list["exit_type"].append(log->exit_type);
            log_list["pl_points"].append(log->pl_points);
            log_list["re_pnl"].append(log->re_pnl);
            log_list["comm"].append(log->commission);
        }

        for (auto &key : {"ticker", "entry_date", "entry_price", "entry_type",
                          "size", "exit_date", "exit_price", "exit_type",
                          "pl_points", "re_pnl", "comm"}) {
            log_dict[key] = log_list[key];
        }
        return log_dict;
    };

    py::dict trade_log_long() {
        auto &match_engine = env->recorder->match_engine;
        if (!match_engine->left_trade_settled) {
            match_engine->append_left_trade_to_log();
            match_engine->left_trade_settled = true;
        }
        py::dict log_dict;
        map<string, py::list> log_list;
        for (auto &log : match_engine->finished_log) {
            if (log->entry_type.find("Buy") != string::npos) {
                log_list["ticker"].append(log->ticker);
                log_list["entry_date"].append(log->entry_date);
                log_list["entry_price"].append(log->entry_price);
                log_list["entry_type"].append(log->entry_type);
                log_list["size"].append(log->size);
                log_list["exit_date"].append(log->exit_date);
                log_list["exit_price"].append(log->exit_price);
                log_list["exit_type"].append(log->exit_type);
                log_list["pl_points"].append(log->pl_points);
                log_list["re_pnl"].append(log->re_pnl);
                log_list["comm"].append(log->commission);
            }
        }

        for (auto &key : {"ticker", "entry_date", "entry_price", "entry_type",
                          "size", "exit_date", "exit_price", "exit_type",
                          "pl_points", "re_pnl", "comm"}) {
            log_dict[key] = log_list[key];
        }
        return log_dict;
    };

    py::dict trade_log_short() {
        auto &match_engine = env->recorder->match_engine;
        if (!match_engine->left_trade_settled) {
            match_engine->append_left_trade_to_log();
            match_engine->left_trade_settled = true;
        }
        py::dict log_dict;
        map<string, py::list> log_list;
        for (auto &log : match_engine->finished_log)
            if (log->entry_type.find("Short")!= string::npos) {
                log_list["ticker"].append(log->ticker);
                log_list["entry_date"].append(log->entry_date);
                log_list["entry_price"].append(log->entry_price);
                log_list["entry_type"].append(log->entry_type);
                log_list["size"].append(log->size);
                log_list["exit_date"].append(log->exit_date);
                log_list["exit_price"].append(log->exit_price);
                log_list["exit_type"].append(log->exit_type);
                log_list["pl_points"].append(log->pl_points);
                log_list["re_pnl"].append(log->re_pnl);
                log_list["comm"].append(log->commission);
            }

        for (auto &key : {"ticker", "entry_date", "entry_price", "entry_type",
                          "size", "exit_date", "exit_price", "exit_type",
                          "pl_points", "re_pnl", "comm"}) {
            log_dict[key] = log_list[key];
        }
        return log_dict;
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

void export_OnePiece() {
    using namespace boost::python;
    class_<OnePieceWrapper>("OnePiece")
        .def("sunny", &OnePieceWrapper::sunny)
        .def("set_date", &OnePieceWrapper::set_date)
        .def("set_stock_backtest", &OnePieceWrapper::set_stock_backtest)
        .add_property("tickers", &OnePieceWrapper::tickers)
        .add_property("balance", &OnePieceWrapper::balance)
        .add_property("cash", &OnePieceWrapper::cash)
        .add_property("frozen_cash", &OnePieceWrapper::frozen_cash)
        .add_property("holding_pnl", &OnePieceWrapper::holding_pnl)
        .add_property("realized_pnl", &OnePieceWrapper::realized_pnl)
        .add_property("commission", &OnePieceWrapper::commission)
        .add_property("margin", &OnePieceWrapper::margin)
        .add_property("position", &OnePieceWrapper::position)
        .add_property("avg_price", &OnePieceWrapper::avg_price)
        .add_property("trade_log", &OnePieceWrapper::trade_log)
        .add_property("trade_log_long", &OnePieceWrapper::trade_log_long)
        .add_property("trade_log_short", &OnePieceWrapper::trade_log_short);
};
