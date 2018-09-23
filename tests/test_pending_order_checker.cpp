#include "setting_for_test.hpp"
#include "sys_module/components/OrderGenerator.h"
#include "sys_module/components/PendingOrderChecker.h"
#include "sys_module/models/BarBase.h"
#include "sys_module/models/GeneralOrder.h"
#include "utils/arrow.h"
#include "utils/utils.h"
#include <gtest/gtest.h>

TEST(TestPendingOrder, Submit) {
    using namespace op;
    using namespace utils;
    auto go = SettingFunc::global_setting();
    auto strategy = go.env->strategies["DemoStrategy"];

    OrderGenerator order_generator;
    PendingOrderChecker pending_order_checker;
    auto order_checker = go.env->brokers["StockBroker"]->checker;
    go.env->execute_on_close_or_next_open = "open";

    double CLOSE = 11;
    double HIGH = 20;
    double LOW = 5;
    double NEXT_OPEN = 10;

    const_cast<double &>(go.env->feeds[TICKER]->current_ohlc->close) = CLOSE;
    const_cast<double &>(go.env->feeds[TICKER]->current_ohlc->high) = HIGH;
    const_cast<double &>(go.env->feeds[TICKER]->current_ohlc->low) = LOW;
    const_cast<double &>(go.env->feeds[TICKER]->next_ohlc->open) = NEXT_OPEN;

    //挂单带pending
    go.env->initialize_env();
    strategy->buy(100, TICKER,
                  0,    //takeprofit
                  0.01, //takeprofit_pct
                  0,    //stoploss
                  0,    //stoploss_pct
                  0,    //trailingstop
                  0,    //trailingstop_pct
                  12,   //price
                  0);   //price_pct

    order_generator.run(); // 提交订单到挂单
    ASSERT_EQ(go.env->orders_pending.size(), 1);

    pending_order_checker.run(); // 触发mkt挂单生成信号
    ASSERT_EQ(go.env->orders_pending.size(), 0);
    ASSERT_EQ(go.env->signals_trigger_cur.size(), 1);
    ASSERT_EQ(go.env->orders_child_of_mkt_dict.size(), 0);

    order_generator.run(); // mkt挂单信号生成为order
    ASSERT_EQ(go.env->orders_mkt_absolute_cur.size(), 1);
    ASSERT_EQ(go.env->signals_trigger_cur.size(), 0);
    ASSERT_EQ(go.env->orders_child_of_mkt_dict.size(), 1); // 伴随takeprofit挂单

    pending_order_checker.run(); // takeprofit触发生成信号
    ASSERT_EQ(go.env->signals_trigger_cur.size(), 1);

    order_generator.run(); // takeprofit 信号生成为order
    ASSERT_EQ(go.env->orders_mkt_absolute_cur.size(), 2);
    ASSERT_EQ(go.env->signals_trigger_cur.size(), 0);
    ASSERT_EQ(go.env->orders_mkt_absolute_cur[0]->execute_price, 12);
    ASSERT_EQ(go.env->orders_mkt_absolute_cur[1]->execute_price,
              Math::Round(12 * 1.01, 3));

    // 市价单带pending
    go.env->initialize_env();
    strategy->buy(100, TICKER,
                  0,    //takeprofit
                  0.01, //takeprofit_pct
                  0,    //stoploss
                  0,    //stoploss_pct
                  0,    //trailingstop
                  0,    //trailingstop_pct
                  0,    //price
                  0);

    order_generator.run(); // 生成市价单
    ASSERT_EQ(go.env->signals_trigger_cur.size(), 0);
    ASSERT_FALSE(go.env->orders_child_of_mkt_dict.empty());
    ASSERT_EQ(go.env->orders_mkt_normal_cur.size(), 1);

    pending_order_checker.run(); // 生成挂单触发信号
    ASSERT_EQ(go.env->orders_child_of_mkt_dict.size(), 0);
    ASSERT_EQ(go.env->signals_trigger_cur.size(), 1);

    order_generator.run(); // 挂单信号成交并转化为order
    ASSERT_EQ(go.env->orders_mkt_absolute_cur.size(), 1);
    ASSERT_EQ(go.env->orders_mkt_absolute_cur.back()->execute_price,
              Math::Round(NEXT_OPEN * 1.01, 3));
    ASSERT_EQ(go.env->signals_trigger_cur.size(), 0);
    ASSERT_EQ(go.env->orders_mkt_absolute_cur.size(), 1);
}
