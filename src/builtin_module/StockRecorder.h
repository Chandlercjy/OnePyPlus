#include "../sys_module/RecorderBase.h"
#include <string>
#pragma once

namespace sys {
using std::string;
class Environment;
class BarBase;

class StockRecorder : public RecorderBase {
  public:
    StockRecorder();
    std::shared_ptr<BarBase> bar_class(const string &ticker,
                                       const string &frequency) override;
};
} // namespace sys
