#include "DataType.h"
#include "builtin_module/backtest_stock/ForexBroker.h"
#include "sys_module/BrokerBase.h"
#include "sys_module/RecorderBase.h"
#include "sys_module/components/SubmitOrderChecker.h"
#include "sys_module/models/GeneralOrder.h"
#include "utils/easy_func.h"

OP_NAMESPACE_START
using ForexUtils = utils::ForexUtils;

ForexBroker::ForexBroker() {
    checker = make_shared<SubmitOrderChecker>(cash_func());
    auto module = make_shared<ForexBroker>(*this);
    env->save_module("ForexBroker", module);
}

double forex_cash_func(const MarketOrderPtr &order) {
    static Environment* env = Environment::get_instance();
    auto &ticker = order->ticker;
    auto size = order->size;
    auto execute_price = order->execute_price;
    auto margin_rate = env->recorder->margin_rate;
    auto mult = ForexUtils::market_value_multiplyer(ticker, execute_price);

    auto slippage = utils::Forex_slippage[ticker];
    auto commission = (slippage * size / 1e5 *
                       ForexUtils::dollar_per_pips(ticker, execute_price));

    return size * execute_price * margin_rate * mult + commission;
}

Cash_func_ptr_type ForexBroker::cash_func() {
    return &forex_cash_func;
};

OP_NAMESPACE_END
