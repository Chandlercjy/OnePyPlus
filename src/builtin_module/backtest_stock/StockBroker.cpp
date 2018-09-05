#include "DataType.h"
#include "builtin_module/backtest_stock/StockBroker.h"
#include "sys_module/BrokerBase.h"
#include "sys_module/components/SubmitOrderChecker.h"
#include "sys_module/models/GeneralOrder.h"

OP_NAMESPACE_START
using std::make_shared;

StockBroker::StockBroker() {
    checker = make_shared<SubmitOrderChecker>(cash_func());
    auto module = make_shared<StockBroker>(*this);
    env->save_module("StockBroker", module);
}

double stock_cash_func(const MarketOrderPtr &order) {
    return order->size * order->execute_price;
}

Cash_func_ptr_type StockBroker::cash_func() {
    return &stock_cash_func;
};

OP_NAMESPACE_END
