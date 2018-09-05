#include "setting_for_test.hpp"
//#include "sys_module/BrokerBase.h"
//#include "sys_module/components/MarketMaker.h"
#include "sys_module/components/OrderGenerator.h"
//#include "sys_module/components/SubmitOrderChecker.h"
//#include "sys_module/models/BarBase.h"
//#include "sys_module/models/GeneralOrder.h"
//#include "sys_module/models/SeriesBase.h"
#include "utils/arrow.h"
#include <gtest/gtest.h>

TEST(TestPendingOrder, Submit) {
    using namespace op;
    auto go = SettingFunc::global_setting();
    auto strategy = go.env->strategies["DemoStrategy"];

    OrderGenerator order_generator;
    auto order_checker = go.env->brokers["StockBroker"]->checker;
    go.env->execute_on_close_or_next_open = "open";
    //double NEXT_OPEN = 10;
}
