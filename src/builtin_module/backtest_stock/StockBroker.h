#include "../../sys_module/BrokerBase.h"

#pragma once

namespace sys {
using std::shared_ptr;

class MarketOrder;

class StockBroker : public BrokerBase {
  public:
    StockBroker();

  private:
    const double _required_cash_func(const shared_ptr<MarketOrder> &order) override;
};

} // namespace sys
