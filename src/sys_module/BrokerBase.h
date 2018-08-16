#pragma once

namespace sys {
class Environment;
class BrokerBase {
  public:
    BrokerBase() = default;
    BrokerBase(const BrokerBase &) = default;
    BrokerBase &operator=(const BrokerBase &) = default;
    Environment *env;
    void run();
    virtual ~BrokerBase() = default;

  protected:
    template <typename broker_name>
    void save_to_env(const broker_name *self_ptr);
};
} // namespace sys
