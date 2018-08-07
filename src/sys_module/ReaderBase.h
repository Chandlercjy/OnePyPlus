#pragma once

#include "../TypeDef.h"
#include <string>
#include <vector>

namespace sys {
using std::string;
using std::vector;

class ReaderBase {
  public:
    //ReaderBase(const string &ticker) : ticker(ticker){};
    const string ticker;
    virtual OhlcVector::iterator load(const string &fromdate,
                                      const string &todate,
                                      const string &frequency) = 0;

    OhlcVector::iterator load_by_cleaner(const string &fromdate,
                                         const string &todate,
                                         const string &frequency);

  private:
    //_check_readers_key();
};
} // namespace sys
