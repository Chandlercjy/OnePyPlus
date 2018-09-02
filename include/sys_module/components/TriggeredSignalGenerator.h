#include <string>

#pragma once

namespace op {
using std::shared_ptr;
using std::string;
class PendingOrderBase;

class TriggeredSignalGenerator {
  public:
    TriggeredSignalGenerator() = delete;

    static void _generate_bare_signal(const shared_ptr<PendingOrderBase> &order);

    static void _generate_full_signal(const shared_ptr<PendingOrderBase> &order);

    static bool generate_triggered_signal(const shared_ptr<PendingOrderBase> &order);
};

} // namespace op
