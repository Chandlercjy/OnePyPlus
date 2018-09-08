#include <iostream>

void greet() {
    std::cout<< "hello, world";
};

#include <boost/python.hpp>

BOOST_PYTHON_MODULE(OnePyPlus) {
    using namespace boost::python;
    def("greet", greet);
}
