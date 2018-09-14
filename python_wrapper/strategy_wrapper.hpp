#include "Environment.h"
#include "sys_module/RecorderBase.h"
#include "sys_module/StrategyBase.h"
#include "sys_module/models/SeriesBase.h"
#include <boost/python.hpp>
#include <boost/python/overloads.hpp>

#pragma once

namespace py = boost::python;
using namespace op;

py::tuple buy(const double size,
              const string &ticker,
              const double takeprofit = 0,
              const double takeprofit_pct = 0,
              const double stoploss = 0,
              const double stoploss_pct = 0,
              const double trailingstop = 0,
              const double trailingstop_pct = 0,
              const double price = 0,
              const double price_pct = 0) {
    return py::make_tuple(size, ticker, takeprofit, takeprofit_pct, stoploss,
                          stoploss_pct, trailingstop, trailingstop_pct, price,
                          price_pct);
};

py::tuple sell(const double size,
               const string &ticker,
               const double price = 0,
               const double price_pct = 0) {
    return py::make_tuple(size, ticker, price, price_pct);
};

py::tuple shortsell(const double size,
                    const string &ticker,
                    const double takeprofit = 0,
                    const double takeprofit_pct = 0,
                    const double stoploss = 0,
                    const double stoploss_pct = 0,
                    const double trailingstop = 0,
                    const double trailingstop_pct = 0,
                    const double price = 0,
                    const double price_pct = 0) {
    return py::make_tuple(size, ticker, takeprofit, takeprofit_pct, stoploss,
                          stoploss_pct, trailingstop, trailingstop_pct, price,
                          price_pct);
};

py::tuple cover(const double size,
                const string &ticker,
                const double price = 0,
                const double price_pct = 0) {
    return py::make_tuple(size, ticker, price, price_pct);
};

py::tuple cancel_pending(const string &ticker,
                         const string &long_or_short,
                         const double below_price,
                         const double above_price = 0) {
    return py::make_tuple(ticker, long_or_short, below_price, above_price);
}

py::tuple cancel_tst(const string &ticker,
                     const string &long_or_short,
                     const bool takeprofit = false,
                     const bool stoploss = false,
                     const bool trailingstop = false) {
    return py::make_tuple(ticker, long_or_short, takeprofit,
                          stoploss, trailingstop);
};

BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(buy_overloads, buy, 2, 10);
BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(sell_overloads, sell, 2, 4);
BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(shortsell_overloads, shortsell, 2, 10);
BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(cover_overloads, cover, 2, 4);
BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(cancel_pending_overloads, cancel_pending, 2, 4);
BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(cancel_tst_overloads, cancel_tst, 2, 5);

struct StrategyBaseWrapper : StrategyBase, py::wrapper<StrategyBase> {
    StrategyBaseWrapper(const string &name)
        : StrategyBase(name){};

    virtual void handle_bar() override {
        if (py::override n = this->get_override("handle_bar"))
            n();
        else
            default_handle_bar();
    };

    void default_handle_bar() { throw std::logic_error("handle_bar in Strategy should be override"); };

    void save_to_env(StrategyBaseWrapper *strategy) {
        auto module = make_shared<StrategyBaseWrapper>(*strategy);
        env->save_module(strategy->strategy_name, module);
    };

    Environment *get_env() {
        return env;
    };
};

void export_StrategyBase() {
    using namespace boost::python;
    const char *buy_short_doc = "size, ticker, takeprofit, takeprofit_pct,\
                                    stoploss, stoploss_pct, trailingstop,\
                                    trailingstop_pct, price, price_pct";

    const char *sell_cover_doc = "size, ticker, price, price_pct";

    class_<StrategyBaseWrapper, boost::noncopyable>("StrategyBase", init<string>())
        .def("handle_bar", &StrategyBaseWrapper::handle_bar, &StrategyBaseWrapper::default_handle_bar)
        .def("buy", &StrategyBaseWrapper::buy,
             buy_overloads(args("size", "ticker", "takeprofit", "takeprofit_pct",
                                "stoploss", "stoploss_pct", "trailingstop",
                                "trailingstop_pct", "price", "price_pct"),
                           buy_short_doc))
        .def("sell", &StrategyBaseWrapper::sell,
             sell_overloads(args("size", "ticker", "price", "price_pct"),
                            sell_cover_doc))
        .def("short", &StrategyBaseWrapper::shortsell,
             shortsell_overloads(args("size", "ticker", "takeprofit", "takeprofit_pct",
                                      "stoploss", "stoploss_pct", "trailingstop",
                                      "trailingstop_pct", "price", "price_pct"),
                                 buy_short_doc))
        .def("cover", &StrategyBaseWrapper::cover,
             cover_overloads(args("size", "ticker", "price", "price_pct"),
                             sell_cover_doc))

        .def("cancel_pending", &StrategyBaseWrapper::cancel_pending,
             cancel_pending_overloads(args("ticker", "long_or_short",
                                           "below_price", "above_price"),
                                      "ticker, long_or_short, below_price, above_price"))

        .def("cancel_tst", &StrategyBaseWrapper::cancel_tst,
             cancel_tst_overloads(args("ticker", "long_or_short",
                                       "takeprofit", "stoploss", "trailingstop"),
                                  "ticker, long_or_short, below_price, above_price"))

        .def("save_to_env", &StrategyBaseWrapper::save_to_env)
        .def("get_env", &StrategyBaseWrapper::get_env, return_value_policy<reference_existing_object>());
};
