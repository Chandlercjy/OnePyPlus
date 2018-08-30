#include <string>
#pragma once

using std::string;

namespace sys {
class Environment;

class CleanerBase {

  public:
    CleanerBase();

    Environment *env;

    int bufferday;

    void run();
    virtual ~CleanerBase() = default;

    void initialize_buffer_data(const string &ticker, int &bufferday);

  protected:
    template <typename cleaner_name>
    void save_to_env(const cleaner_name *self_ptr);
    static int _counter;
};
int CleanerBase::_counter = 1;
} // namespace sys
