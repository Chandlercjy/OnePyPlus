
#pragma once

namespace sys {
class RecorderBase {
  public:
    void run();
    virtual ~RecorderBase() = default;
};
} // namespace sys
