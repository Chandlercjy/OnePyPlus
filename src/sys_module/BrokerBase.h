#pragma once

namespace sys {
class BrokerBase {
  public:
    void run();
    virtual ~BrokerBase() = default;
};
} // namespace sys
