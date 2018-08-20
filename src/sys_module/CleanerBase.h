#include <string>
#pragma once

using std::string;

namespace sys {
class Environment;

class CleanerBase {

  public:
    CleanerBase() = default;
    CleanerBase(const CleanerBase &) = default;
    CleanerBase &operator=(const CleanerBase &) = default;
    Environment *env;

    int bufferday;

    void run();
    virtual ~CleanerBase() = default;

    void initialize_buffer_data(const string &ticker, int &bufferday);

  protected:
    template <typename cleaner_name>
    void save_to_env(const cleaner_name *self_ptr);
};
} // namespace sys
