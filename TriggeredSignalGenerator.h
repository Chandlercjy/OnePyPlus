#include <string>

#pragma once

namespace sys {
using std::string;

class TriggeredSignalGenerator {
  public:
    TriggeredSignalGenerator() = delete;
    static void generate_bare_signal();
    static void generate_full_signal();
    static void generate_triggered_signal();
};

} // namespace sys
