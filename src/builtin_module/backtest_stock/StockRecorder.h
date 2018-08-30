#include "../../sys_module/RecorderBase.h"
#include <string>
#pragma once

namespace sys {
using std::shared_ptr;
using std::string;

class Environment;
class BarBase;

class StockRecorder : public RecorderBase {
  public:
    StockRecorder();
    shared_ptr<BarBase> bar_class(const string &ticker,
                                  const string &frequency) override;
    void initialize() override;
    void _update_cash(const string &trading_date) override;
    void set_setting(const double initial_cash,
                     const double comm,
                     const double comm_pct,
                     const double margin_rate) override;
};

} // namespace sys
