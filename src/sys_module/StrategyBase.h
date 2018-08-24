#pragma once

#include <string>

namespace sys {
class Environment;
class StrategyBase {

  public:
    StrategyBase() = default;
    StrategyBase(const StrategyBase &) = default;
    StrategyBase &operator=(const StrategyBase &) = default;
    Environment *env;

    void buy();
    void sell();
    void shortsell();
    void cover();

    void run();
    virtual ~StrategyBase() = default;

  protected:
    template <typename strategy_name>
    void save_to_env(const strategy_name *self_ptr);
};
} // namespace sys
