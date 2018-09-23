#include "DataType.h"
#include <boost/python.hpp>
#include <boost/python/suite/indexing/map_indexing_suite.hpp>
#include <boost/python/suite/indexing/vector_indexing_suite.hpp>

#pragma once
void export_DataType() {
    using namespace op;
    using namespace boost::python;
    using StringList = vector<string>;
    class_<StringList>("StringList")
        .def(vector_indexing_suite<StringList>());

    using Dict_StrList = map<string, vector<string>>;
    class_<Dict_StrList>("Dict_StrList")
        .def(map_indexing_suite<Dict_StrList>());

    using Deque_str = deque<string>;
    class_<Deque_str>("Deque_str")
        .def(vector_indexing_suite<Deque_str>());

    using Deque_double = deque<double>;
    class_<Deque_double>("Deque_double")
        .def(vector_indexing_suite<Deque_double>());

    using CleanerData = map<string, CleanerDataStruct>;
    class_<CleanerData>("CleanerDataDict")
        .def(map_indexing_suite<CleanerData>());
}
