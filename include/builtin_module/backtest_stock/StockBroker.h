#include "DataType.h"
#include "OP_DECLARE.h"
#include "sys_module/BrokerBase.h"

#pragma once

OP_NAMESPACE_START

class MarketOrder;

class StockBroker : public BrokerBase {

  public:
    StockBroker();

  private:
    Cash_func_ptr_type cash_func() override;
};

OP_NAMESPACE_END
