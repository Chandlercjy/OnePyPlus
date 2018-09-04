#include "Exceptions.h"
#include "SignalChecker.h"

OP_NAMESPACE_START

void SignalChecker::check_conflict(const double obj,
                                   const double obj_pct,
                                   const string &name) {
    if (obj != 0 && obj_pct != 0)
        throw except::OrderConflictError(); //TODO

    if (obj_pct != 0 && (obj_pct <= -1 || obj_pct >= 1))
        throw except::PctRangeError(); //TODO

    if (name != "price") {
        if (obj < 0)
            throw std::logic_error("{name.upper()} should be Positive");
        else if (obj_pct < 0)
            throw std::logic_error("{name.upper()} should be Positive");
    }
};

void SignalChecker::check_size(const int size) {
    if (size < 0)
        throw std::logic_error("size should be Positive");
};

OP_NAMESPACE_END
