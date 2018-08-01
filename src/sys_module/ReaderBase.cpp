
#include "ReaderBase.h"

OhlcVector::iterator ReaderBase::load_by_cleaner(const string &fromdate,
                                                 const string &todate,
                                                 const string &frequency) {
    return this->load(fromdate, todate, frequency);
};
