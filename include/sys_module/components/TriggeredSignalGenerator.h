#include <string>

#pragma once

namespace op {
using std::string;

class TriggeredSignalGenerator {
  public:
    TriggeredSignalGenerator() = delete;

    template <typename T>
    static void _generate_bare_signal(const T &order);

    template <typename T>
    static void _generate_full_signal(const T &order);

    template <typename T>
    static bool generate_triggered_signal(const T &order);
};

} // namespace op

