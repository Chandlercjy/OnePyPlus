#pragma once

#include "../DataType.h"
#include <string>
#include <vector>

namespace sys {
using std::string;

class ReaderBase {
  public:
    ReaderBase(const string &ticker) : ticker(ticker){};
    const string ticker;
    virtual OhlcVector::const_iterator load(const string &fromdate,
                                            const string &todate,
                                            const string &frequency) = 0;

    OhlcVector::const_iterator load_by_cleaner(const string &fromdate,
                                               const string &todate,
                                               const string &frequency);
    virtual ~ReaderBase() = default;

  private:
    //_check_readers_key();
};
} // namespace sys
