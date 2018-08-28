#include <string>

#pragma once

namespace sys {
using std::string;
class Environment;
class RiskManagerBase {
  public:
    RiskManagerBase();
    Environment *env;

    virtual const string get_name() = 0;
    void run();

  protected:
    template <typename risk_manager_name>
    void save_to_env(const risk_manager_name *self_ptr);
};
} // namespace sys
