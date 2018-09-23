#include "Environment.h"
#include "sys_module/CleanerBase.h"
#include "type_wrapper.hpp"
#include <boost/python.hpp>

#pragma once
namespace py = boost::python;
using namespace op;

py::tuple get(const string &ticker) {
    return py::make_tuple(ticker);
};

struct CleanerBaseWrapper : CleanerBase, py::wrapper<CleanerBase> {
    CleanerBaseWrapper(const string &name,
                       const int rolling_window,
                       int buffer_day,
                       const string &frequency)
        : CleanerBase(name, rolling_window, buffer_day, frequency){};

    ~CleanerBaseWrapper() {
        CleanerBase::~CleanerBase();
    }

    virtual double calculate(const string &ticker) override {
        if (py::override n = this->get_override("calculate"))
            n(ticker);
        else
            default_calculate(ticker);
        return 0;
    };

    double default_calculate(const string &ticker) {
        throw std::logic_error("calculate in Cleaner should be override");
        return 0;
    };

    void save_to_env(CleanerBaseWrapper *cleaner) {
        auto module = make_shared<CleanerBaseWrapper>(*cleaner);
        env->save_module(cleaner->name, module);
    };

    CleanerData *get_data() {
        return &data;
    };
};

void export_CleanerBase() {
    using namespace boost::python;

    class_<CleanerDataStruct>("CleanerDataStruct", init<string>())
        .add_property("date", &CleanerDataStruct::date)
        .add_property("open", &CleanerDataStruct::open)
        .add_property("high", &CleanerDataStruct::high)
        .add_property("low", &CleanerDataStruct::low)
        .add_property("close", &CleanerDataStruct::close)
        .add_property("volume", &CleanerDataStruct::volume);

    class_<CleanerBaseWrapper, boost::noncopyable>(
        "CleanerBase", init<string, int, int, string>())
        .add_property("frequency", &CleanerBaseWrapper::frequency)
        .def("calculate", &CleanerBaseWrapper::calculate, &CleanerBaseWrapper::default_calculate)
        .def("save_to_env", &CleanerBaseWrapper::save_to_env)
        .def("get_data", &CleanerBaseWrapper::get_data, return_value_policy<reference_existing_object>());
};
