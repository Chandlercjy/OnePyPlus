#include "DataType.h"
#include "sys_module/BrokerBase.h"

#pragma once

namespace sys {
using std::shared_ptr;

class MarketOrder;

class StockBroker : public BrokerBase {

  public:
    StockBroker();

  private:
    Cash_func_ptr_type cash_func() override;
};

} // namespace sys
