#include "../../sys_module/BrokerBase.h"

#pragma once

namespace sys {
using std::shared_ptr;

class MarketOrder;

class StockBroker : public BrokerBase {

  public:
    StockBroker();

  private:
    using Cash_func_ptr_type = double (*)(const shared_ptr<MarketOrder> &order);
    //const double _required_cash_func(const shared_ptr<MarketOrder> &order) ;
    Cash_func_ptr_type cash_func() override;
};

} // namespace sys
