#include <string>
#pragma once

using std::string;

namespace op {
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
    template <typename T>
    void save_to_env(const T *self_ptr, const string &name);
    static int _counter;
};
int CleanerBase::_counter = 1;
} // namespace op

