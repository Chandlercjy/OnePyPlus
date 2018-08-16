#pragma once

#include "../DataType.h"
#include <string>
#include <vector>

namespace sys {
using std::string;
class Environment;

class ReaderBase {
  public:
    ReaderBase(const string &ticker);
    ReaderBase(const ReaderBase &) = default;
    ReaderBase &operator=(const ReaderBase &) = default;
    Environment *env;
    const string ticker;
    virtual std::shared_ptr<OhlcVector> load(const string &fromdate,
                                             const string &todate,
                                             const string &frequency) = 0;

    std::shared_ptr<OhlcVector> load_by_cleaner(const string &fromdate,
                                                const string &todate,
                                                const string &frequency);
    virtual ~ReaderBase() = default;

  protected:
    template <typename reader_name>
    void save_to_env(const reader_name *self_ptr);
    //private:
    //_check_readers_key();
};
} // namespace sys
