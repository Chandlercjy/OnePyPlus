#include "builtin_module/CsvReader.h"
#include "builtin_module/backtest_stock/StockRecorder.h"
#include "setting_for_test.hpp"
#include "sys_module/BrokerBase.h"
#include "sys_module/components/MarketMaker.h"
#include "sys_module/components/OrderGenerator.h"
#include "sys_module/components/SubmitOrderChecker.h"
#include "sys_module/models/BarBase.h"
#include "sys_module/models/GeneralOrder.h"
#include "sys_module/models/SeriesBase.h"
#include "utils/arrow.h"
#include <gtest/gtest.h>

class TestSubmit : public ::testing::Test {
  public:
    void settle_next_open(op::OnePiece &go, const double next_open) {
        go.env->initialize_env();
        go.market_maker->initialize();
        go.market_maker->update_market();
        go.env->execute_on_close_or_next_open = "open";
        auto &open = go.env->feeds[op::TICKER]->next_ohlc->open;
        const_cast<double &>(open) = next_open;
    };
};

TEST_F(TestSubmit, Submit) {
    using namespace op;
    auto go = SettingFunc::global_setting();
    auto strategy = go.env->strategies["DemoStrategy"];

    OrderGenerator order_generator;
    auto order_checker = go.env->brokers["StockBroker"]->checker;
    go.env->execute_on_close_or_next_open = "open";
    double NEXT_OPEN = 10;

    ////测试 缺少position
    settle_next_open(go, NEXT_OPEN);
    strategy->sell(100, TICKER);
    strategy->cover(100, TICKER);
    order_generator.run();
    order_checker->run();
    ASSERT_TRUE(go.env->cur_suspended_tickers.empty());
    ASSERT_TRUE(go.env->orders_mkt_submitted_cur.empty());

    // 测试 缺少cash
    settle_next_open(go, NEXT_OPEN);
    strategy->buy(100, TICKER);
    strategy->buy(100, TICKER);
    go.env->recorder->cash->data[0].value = NEXT_OPEN * 100;
    order_generator.run();
    order_checker->run();
    ASSERT_TRUE(go.env->cur_suspended_tickers.empty());
    ASSERT_EQ(go.env->orders_mkt_submitted_cur.size(), 1);

    settle_next_open(go, NEXT_OPEN);
    strategy->buy(100, TICKER);
    strategy->buy(100, TICKER);
    go.env->recorder->cash->data[0].value = NEXT_OPEN * 100 - 1;
    order_generator.run();
    order_checker->run();
    ASSERT_TRUE(go.env->orders_mkt_submitted_cur.empty());

    settle_next_open(go, NEXT_OPEN);
    strategy->buy(100, TICKER);
    strategy->buy(100, TICKER);
    go.env->recorder->cash->data[0].value = NEXT_OPEN * 100 + 1;
    order_generator.run();
    order_checker->run();
    ASSERT_EQ(go.env->orders_mkt_submitted_cur.size(), 1);

    //测试 partial 成交;
    settle_next_open(go, NEXT_OPEN);
    strategy->sell(100, TICKER);
    strategy->cover(100, TICKER);
    string long_name = TICKER + "_long";
    string short_name = TICKER + "_short";
    double long_po = go.env->recorder->position->data[long_name][0].value = 30;
    double short_po = go.env->recorder->position->data[short_name][0].value = 40;
    order_generator.run();
    order_checker->run();
    assert(go.env->orders_mkt_submitted_cur.size() == 2);

    for (auto &order : go.env->orders_mkt_submitted_cur)
        if (order->get_action_type() == ActionType::Sell)
            ASSERT_EQ(order->size, long_po);
        else if (order->get_action_type() == ActionType::Cover)
            ASSERT_EQ(order->size, short_po);
        else
            throw std::logic_error("This can't be raised");
}
