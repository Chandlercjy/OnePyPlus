#include "DataType.h"
#include "builtin_module/backtest_stock/StockBroker.h"
#include "sys_module/BrokerBase.h"
#include "sys_module/components/SubmitOrderChecker.h"
#include "sys_module/models/GeneralOrder.h"

namespace op {
using std::make_shared;

StockBroker::StockBroker() {
    _checker = make_shared<SubmitOrderChecker>(cash_func());
    auto module = make_shared<StockBroker>(*this);
    env->save_module("StockBroker", module);
}

//const double StockBroker::_required_cash_func(const shared_ptr<MarketOrder> &order) {
//return order->size * order->execute_price;
//};

double stock_cash_func(const shared_ptr<MarketOrder> &order) {
    return order->size * order->execute_price;
}

Cash_func_ptr_type StockBroker::cash_func() {
    return &stock_cash_func;
};

} // namespace op
