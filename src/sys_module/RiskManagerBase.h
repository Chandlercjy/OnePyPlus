#pragma once

namespace sys {
class Environment;
class RiskManagerBase {
  public:
    RiskManagerBase() = default;
    RiskManagerBase(const RiskManagerBase &) = default;
    RiskManagerBase &operator=(const RiskManagerBase &) = default;
    Environment *env;

    void run();
    virtual ~RiskManagerBase() = default;

  protected:
    template <typename risk_manager_name>
    void save_to_env(const risk_manager_name *self_ptr);
};
} // namespace sys
