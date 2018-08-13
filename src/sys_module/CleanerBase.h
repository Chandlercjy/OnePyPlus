
#pragma once

namespace sys {
class CleanerBase {

  public:
    void run();
    virtual ~CleanerBase() = default;
};
} // namespace sys
