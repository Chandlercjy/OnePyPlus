#pragma once
#include <string>

namespace utils {

using std::string;
int get_second_ratio(const string &frequency) {
    int result = 0;
    if (frequency == "S5")
        result = 5;
    else if (frequency == "S10")
        result = 10;
    else if (frequency == "S30")
        result = 30;
    else if (frequency == "M1")
        result = 60;
    else if (frequency == "M2")
        result = 120;
    else if (frequency == "M4")
        result = 240;
    else if (frequency == "M5")
        result = 300;
    else if (frequency == "M10")
        result = 600;
    else if (frequency == "M15")
        result = 900;
    else if (frequency == "M30")
        result = 1800;
    else if (frequency == "H1")
        result = 3600;
    else if (frequency == "H2")
        result = 7200;
    else if (frequency == "H3")
        result = 10800;
    else if (frequency == "H4")
        result = 14400;
    else if (frequency == "H8")
        result = 28800;
    else if (frequency == "H12")
        result = 43200;
    else if (frequency == "D")
        result = 86400;
    return result;
};
} // namespace utils
