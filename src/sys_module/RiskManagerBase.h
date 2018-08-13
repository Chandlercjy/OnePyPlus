#pragma once

namespace sys {
class RiskManagerBase {
  public:
    void run();
    virtual ~RiskManagerBase() = default;
};
} // namespace sys
