#include <string>

#pragma once

namespace op {
using std::string;
class Environment;
class RiskManagerBase {
  public:
    RiskManagerBase();
    Environment *env;

    virtual const string get_name() = 0;
    void run();

  protected:
    template <typename T>
    void save_to_env(const T *self_ptr, const string &name);
};
} // namespace op

