#include "ReaderBase.h"

namespace sys {

OhlcVector::iterator ReaderBase::load_by_cleaner(const string &fromdate,
                                                 const string &todate,
                                                 const string &frequency) {
    return load(fromdate, todate, frequency);
};
} // namespace sys
