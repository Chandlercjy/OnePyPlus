#include "../Environment.h"
#include "ReaderBase.h"

namespace sys {

ReaderBase::ReaderBase(const string &ticker)
    : env(Environment::get_instance()),
      ticker(ticker){};

std::shared_ptr<OhlcVector> ReaderBase::load_by_cleaner(const string &fromdate,
                                                        const string &todate,
                                                        const string &frequency) {
    return load(fromdate, todate, frequency);
};

template <typename reader_name>
void ReaderBase::save_to_env(const reader_name *self_ptr) {
    env->readers[ticker] = std::make_shared<reader_name>(*self_ptr);
}

} // namespace sys
