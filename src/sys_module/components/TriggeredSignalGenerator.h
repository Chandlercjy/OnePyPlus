#include <string>

#pragma once

namespace sys {
using std::string;

class TriggeredSignalGenerator {
  public:
    TriggeredSignalGenerator() = delete;

    template <typename T>
    static void generate_bare_signal(const T &order);

    template <typename T>
    static void generate_full_signal(const T &order);

    template <typename T>
    static void generate_triggered_signal(const T &order);
};

} // namespace sys
