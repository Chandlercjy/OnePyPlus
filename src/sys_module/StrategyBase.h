#pragma once

namespace sys {
class StrategyBase {

  public:
    void run();
    virtual ~StrategyBase() = default;
};
} // namespace sys
