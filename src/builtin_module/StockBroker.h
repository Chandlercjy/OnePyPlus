#include "../sys_module/BrokerBase.h"

#pragma once

namespace sys {

class StockBroker : public BrokerBase {
  public:
      StockBroker();
  private:
    void _required_cash_func() override{};
};

} // namespace sys
