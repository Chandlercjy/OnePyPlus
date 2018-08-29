#include "../sys_module/models/GeneralOrder.h"
#include "StockBroker.h"

namespace sys {
StockBroker::StockBroker() {
    save_to_env(this);
}

const double StockBroker::_required_cash_func(const shared_ptr<MarketOrder> &order) {
    return order->size * order->execute_price;
};

}; // namespace sys
