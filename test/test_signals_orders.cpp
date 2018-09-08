#include "builtin_module/CsvReader.h"
#include "setting_for_test.hpp"
#include "sys_module/components/MarketMaker.h"
#include "sys_module/components/OrderGenerator.h"
#include "sys_module/models/BarBase.h"
#include "sys_module/models/GeneralOrder.h"
#include "sys_module/models/Signal.h"
#include "utils/arrow.h"
#include "utils/utils.h"
#include <gtest/gtest.h>

using namespace op;
using namespace utils;

class TestOrders : public ::testing::Test {
  public:
    OnePiece go = SettingFunc::global_setting();
    shared_ptr<StrategyBase> strategy = go.env->strategies["DemoStrategy"];
    shared_ptr<BrokerBase> broker = go.env->brokers["StockBroker"];
    OrderGenerator order_generator;
    double CLOSE = 11;
    double HIGH = 20;
    double LOW = 5;
    double NEXT_OPEN = 10;

    void test_buy(const double takeprofit,
                  const double stoploss,
                  const double trailingstop,
                  const bool pct) {
        go.env->initialize_env();
        if (pct)
            strategy->buy(100, TICKER,
                          0,            //takeprofit
                          takeprofit,   //takeprofit
                          0,            //stoploss
                          stoploss,     //stoploss
                          0,            //trailingstop
                          trailingstop, //trailingstop
                          0,            //price
                          0);           //price
        else
            strategy->buy(100, TICKER,
                          takeprofit,   //takeprofit
                          0,            //takeprofit_pct
                          stoploss,     //stoploss
                          0,            //stoploss_pct
                          trailingstop, //trailingstop
                          0,            //trailingstop_pct
                          0,            //price
                          0);           //price_pct
        ASSERT_EQ(go.env->signals_normal_cur.size(), 1);
        auto signal = go.env->signals_normal_cur[0];
        ASSERT_EQ(signal->action_type, ActionType::Buy);

        order_generator.run();

        ASSERT_EQ(go.env->orders_mkt_normal_cur.size(), 1);
        auto mkt_order = go.env->orders_mkt_normal_cur[0];
        ASSERT_EQ(mkt_order->signal_info, signal->info);
        ASSERT_FALSE(mkt_order->is_pure());
        ASSERT_EQ(mkt_order->get_cur_price_when_generated(), NEXT_OPEN);
        ASSERT_EQ(mkt_order->execute_price, NEXT_OPEN);

        auto pending_orders = go.env->orders_child_of_mkt_dict[mkt_order->mkt_id];
        auto order_1 = pending_orders[0];
        auto order_2 = pending_orders[1];
        auto order_3 = pending_orders[2];
        ASSERT_EQ(order_1->action_type, ActionType::Sell);
        ASSERT_EQ(order_2->action_type, ActionType::Sell);
        ASSERT_EQ(order_3->action_type, ActionType::Sell);

        ASSERT_EQ(order_1->signal_info, signal->info);
        ASSERT_EQ(order_2->signal_info, signal->info);
        ASSERT_EQ(order_3->signal_info, signal->info);

        ASSERT_EQ(order_1->mkt_id, mkt_order->mkt_id);
        ASSERT_EQ(order_2->mkt_id, mkt_order->mkt_id);
        ASSERT_EQ(order_3->mkt_id, mkt_order->mkt_id);

        if (pct) {
            for (auto &order : go.env->orders_child_of_mkt_dict[mkt_order->mkt_id]) {
                if (order->order_type == OrderType::Stop) {
                    ASSERT_EQ(order->trigger_key, "stoploss_pct");
                    ASSERT_EQ(order->target_price(), Math::Round(NEXT_OPEN * 0.9, 3));
                } else if (order->order_type == OrderType::Limit) {
                    ASSERT_EQ(order->trigger_key, "takeprofit_pct");
                    ASSERT_EQ(order->target_price(), Math::Round(NEXT_OPEN * 1.1, 3));
                } else if (order->order_type == OrderType::Trailing_stop) {
                    ASSERT_EQ(order->trigger_key, "trailingstop_pct");
                    ASSERT_EQ(order->target_price(), Math::Round(NEXT_OPEN * 0.9, 3));
                    ASSERT_GE(order->target_price(), Math::Round(NEXT_OPEN * 0.9, 3));
                    ASSERT_LE(order->target_price(), Math::Round(HIGH - NEXT_OPEN * 0.1, 3));
                } else
                    throw std::logic_error("Never Raised");
            }
        } else {
            for (auto &order : go.env->orders_child_of_mkt_dict[mkt_order->mkt_id]) {
                if (order->order_type == OrderType::Stop) {
                    ASSERT_EQ(order->trigger_key, "stoploss");
                    ASSERT_EQ(order->target_price(), Math::Round(NEXT_OPEN - 0.1, 3));
                } else if (order->order_type == OrderType::Limit) {
                    ASSERT_EQ(order->trigger_key, "takeprofit");
                    ASSERT_EQ(order->target_price(), Math::Round(NEXT_OPEN + 0.1, 3));
                } else if (order->order_type == OrderType::Trailing_stop) {
                    ASSERT_EQ(order->trigger_key, "trailingstop");
                    ASSERT_EQ(order->target_price(), Math::Round(NEXT_OPEN - 0.1, 3));
                    ASSERT_GE(order->target_price(), Math::Round(NEXT_OPEN - 0.1, 3));
                    ASSERT_LE(order->target_price(), Math::Round(HIGH - (NEXT_OPEN - 0.1), 3));
                } else
                    throw std::logic_error("Never Raised");
            }
        }
    };

    void test_short(const double takeprofit,
                    const double stoploss,
                    const double trailingstop,
                    const bool pct) {
        go.env->initialize_env();
        if (pct)
            strategy->shortsell(100, TICKER,
                                0,            //takeprofit
                                takeprofit,   //takeprofit
                                0,            //stoploss
                                stoploss,     //stoploss
                                0,            //trailingstop
                                trailingstop, //trailingstop
                                0,            //price
                                0);           //price
        else
            strategy->shortsell(100, TICKER,
                                takeprofit,   //takeprofit
                                0,            //takeprofit_pct
                                stoploss,     //stoploss
                                0,            //stoploss_pct
                                trailingstop, //trailingstop
                                0,            //trailingstop_pct
                                0,            //price
                                0);           //price_pct
        ASSERT_EQ(go.env->signals_normal_cur.size(), 1);
        auto signal = go.env->signals_normal_cur[0];
        ASSERT_EQ(signal->action_type, ActionType::Short);

        order_generator.run();

        ASSERT_EQ(go.env->orders_mkt_normal_cur.size(), 1);
        auto mkt_order = go.env->orders_mkt_normal_cur[0];
        ASSERT_EQ(mkt_order->signal_info, signal->info);
        ASSERT_FALSE(mkt_order->is_pure());
        ASSERT_EQ(mkt_order->get_cur_price_when_generated(), NEXT_OPEN);
        ASSERT_EQ(mkt_order->execute_price, NEXT_OPEN);

        auto pending_orders = go.env->orders_child_of_mkt_dict[mkt_order->mkt_id];
        auto order_1 = pending_orders[0];
        auto order_2 = pending_orders[1];
        auto order_3 = pending_orders[2];
        ASSERT_EQ(order_1->action_type, ActionType::Cover);
        ASSERT_EQ(order_2->action_type, ActionType::Cover);
        ASSERT_EQ(order_3->action_type, ActionType::Cover);

        ASSERT_EQ(order_1->signal_info, signal->info);
        ASSERT_EQ(order_2->signal_info, signal->info);
        ASSERT_EQ(order_3->signal_info, signal->info);

        ASSERT_EQ(order_1->mkt_id, mkt_order->mkt_id);
        ASSERT_EQ(order_2->mkt_id, mkt_order->mkt_id);
        ASSERT_EQ(order_3->mkt_id, mkt_order->mkt_id);

        if (pct) {
            for (auto &order : go.env->orders_child_of_mkt_dict[mkt_order->mkt_id]) {
                if (order->order_type == OrderType::Stop) {
                    ASSERT_EQ(order->trigger_key, "stoploss_pct");
                    ASSERT_EQ(order->target_price(), Math::Round(NEXT_OPEN * 1.1, 3));
                } else if (order->order_type == OrderType::Limit) {
                    ASSERT_EQ(order->trigger_key, "takeprofit_pct");
                    ASSERT_EQ(order->target_price(), Math::Round(NEXT_OPEN * 0.9, 3));
                } else if (order->order_type == OrderType::Trailing_stop) {
                    ASSERT_EQ(order->trigger_key, "trailingstop_pct");
                    ASSERT_EQ(order->target_price(), Math::Round(NEXT_OPEN * 1.1, 3));
                    ASSERT_GE(order->target_price(), Math::Round(NEXT_OPEN * 1.1, 3));
                    ASSERT_LE(order->target_price(), Math::Round(HIGH + NEXT_OPEN * 0.1, 3));
                } else
                    throw std::logic_error("Never Raised");
            }
        } else {
            for (auto &order : go.env->orders_child_of_mkt_dict[mkt_order->mkt_id]) {
                if (order->order_type == OrderType::Stop) {
                    ASSERT_EQ(order->trigger_key, "stoploss");
                    ASSERT_EQ(order->target_price(), Math::Round(NEXT_OPEN + 0.1, 3));
                } else if (order->order_type == OrderType::Limit) {
                    ASSERT_EQ(order->trigger_key, "takeprofit");
                    ASSERT_EQ(order->target_price(), Math::Round(NEXT_OPEN - 0.1, 3));
                } else if (order->order_type == OrderType::Trailing_stop) {
                    ASSERT_EQ(order->trigger_key, "trailingstop");
                    ASSERT_EQ(order->target_price(), Math::Round(NEXT_OPEN + 0.1, 3));
                    ASSERT_GE(order->target_price(), Math::Round(NEXT_OPEN + 0.1, 3));
                    ASSERT_LE(order->target_price(), Math::Round(HIGH + (NEXT_OPEN - 0.1), 3));
                } else
                    throw std::logic_error("Never Raised");
            }
        }
    };

    // 运行前应先initialized_env
    void test_pending_order(const double target_price,
                            const ActionType action_type,
                            const OrderType order_type) {
        ASSERT_EQ(go.env->signals_pending_cur.size(), 1);
        auto signal = go.env->signals_pending_cur[0];

        ASSERT_EQ(signal->price(), target_price);
        order_generator.run();
        auto pending_order = go.env->orders_pending[0];
        ASSERT_EQ(pending_order->action_type, action_type);
        ASSERT_EQ(pending_order->order_type, order_type);
        ASSERT_EQ(pending_order->target_price(), signal->price());
    };

    // 运行前应先initialized_env
    void test_cancel_pending_order(const string &long_or_short) {
        broker->run();
        ASSERT_EQ(go.env->orders_pending.size(), 3);
        strategy->cancel_pending(TICKER, long_or_short, 0, 20);
        strategy->cancel_pending(TICKER, long_or_short, 3, 0);
        broker->run();
        ASSERT_EQ(go.env->orders_cancel_pending_submitted.size(), 2);
        ASSERT_EQ(go.env->orders_pending.size(), 1);
    };

    void test_cancel_tst_order(const string &long_or_short,
                               const bool takeprofit,
                               const bool stoploss,
                               const bool trailingstop) {
        broker->run();
        ASSERT_EQ(go.env->orders_mkt_submitted_cur.size(), 1);
        auto mkt_id = go.env->orders_mkt_submitted_cur[0]->mkt_id;
        ASSERT_EQ(go.env->orders_child_of_mkt_dict[mkt_id].size(), 1);
        strategy->cancel_tst(TICKER, long_or_short,
                             takeprofit, stoploss, trailingstop);
        broker->run();
        ASSERT_EQ(go.env->orders_child_of_mkt_dict[mkt_id].size(), 0);
    };
};

TEST_F(TestOrders, Orders) {

    go.market_maker->update_market();
    OrderGenerator order_generator;
    go.env->execute_on_close_or_next_open = "open";
    //go.env->is_save_original = true;

    const_cast<double &>(go.env->feeds[TICKER]->current_ohlc->close) = CLOSE;
    const_cast<double &>(go.env->feeds[TICKER]->current_ohlc->high) = HIGH;
    const_cast<double &>(go.env->feeds[TICKER]->current_ohlc->low) = LOW;
    const_cast<double &>(go.env->feeds[TICKER]->next_ohlc->open) = NEXT_OPEN;

    test_buy(10, 10, 10, false);   // 测试 Buy
    test_buy(0.1, 0.1, 0.1, true); // 测试 Buy

    test_short(10, 10, 10, false);   // 测试 short
    test_short(0.1, 0.1, 0.1, true); // 测试 short

    // 测试Sell
    go.env->initialize_env();
    strategy->sell(100, TICKER);
    order_generator.run();
    auto mkt_order = go.env->orders_mkt_normal_cur[0];
    ASSERT_EQ(mkt_order->execute_price, NEXT_OPEN);

    // 测试 Cover;
    go.env->initialize_env();
    strategy->cover(100, TICKER);
    order_generator.run();
    mkt_order = go.env->orders_mkt_normal_cur[0];
    ASSERT_EQ(mkt_order->execute_price, NEXT_OPEN);

    //测试挂单 Buy
    go.env->initialize_env();
    strategy->buy(100, TICKER, 0, 0, 0, 0, 0, 0, 0, 0.01);
    test_pending_order(CLOSE * 1.01, ActionType::Buy, OrderType::Stop);
    go.env->initialize_env();
    strategy->buy(100, TICKER, 0, 0, 0, 0, 0, 0, 0, -0.01);
    test_pending_order(CLOSE * 0.99, ActionType::Buy, OrderType::Limit);
    go.env->initialize_env();
    strategy->buy(100, TICKER, 0, 0, 0, 0, 0, 0, CLOSE + 1, 0);
    test_pending_order(CLOSE + 1, ActionType::Buy, OrderType::Stop);
    go.env->initialize_env();
    strategy->buy(100, TICKER, 0, 0, 0, 0, 0, 0, CLOSE - 1, 0);
    test_pending_order(CLOSE - 1, ActionType::Buy, OrderType::Limit);

    // 测试挂单Sell
    go.env->initialize_env();
    strategy->sell(100, TICKER, 0, 0.01);
    test_pending_order(CLOSE * 1.01, ActionType::Sell, OrderType::Limit);
    go.env->initialize_env();
    strategy->sell(100, TICKER, 0, -0.01);
    test_pending_order(CLOSE * 0.99, ActionType::Sell, OrderType::Stop);
    go.env->initialize_env();
    strategy->sell(100, TICKER, CLOSE + 1, 0);
    test_pending_order(CLOSE + 1, ActionType::Sell, OrderType::Limit);
    go.env->initialize_env();
    strategy->sell(100, TICKER, CLOSE - 1, 0);
    test_pending_order(CLOSE - 1, ActionType::Sell, OrderType::Stop);

    // 测试挂单 Short
    go.env->initialize_env();
    strategy->shortsell(100, TICKER, 0, 0, 0, 0, 0, 0, 0, 0.01);
    test_pending_order(CLOSE * 1.01, ActionType::Short, OrderType::Limit);
    go.env->initialize_env();
    strategy->shortsell(100, TICKER, 0, 0, 0, 0, 0, 0, 0, -0.01);
    test_pending_order(CLOSE * 0.99, ActionType::Short, OrderType::Stop);
    go.env->initialize_env();
    strategy->shortsell(100, TICKER, 0, 0, 0, 0, 0, 0, CLOSE + 1, 0);
    test_pending_order(CLOSE + 1, ActionType::Short, OrderType::Limit);
    go.env->initialize_env();
    strategy->shortsell(100, TICKER, 0, 0, 0, 0, 0, 0, CLOSE - 1, 0);
    test_pending_order(CLOSE - 1, ActionType::Short, OrderType::Stop);

    // 测试挂单 Cover
    go.env->initialize_env();
    strategy->cover(100, TICKER, 0, 0.01);
    test_pending_order(CLOSE * 1.01, ActionType::Cover, OrderType::Stop);
    go.env->initialize_env();
    strategy->cover(100, TICKER, 0, -0.01);
    test_pending_order(CLOSE * 0.99, ActionType::Cover, OrderType::Limit);
    go.env->initialize_env();
    strategy->cover(100, TICKER, CLOSE + 1, 0);
    test_pending_order(CLOSE + 1, ActionType::Cover, OrderType::Stop);
    go.env->initialize_env();
    strategy->cover(100, TICKER, CLOSE - 1, 0);
    test_pending_order(CLOSE - 1, ActionType::Cover, OrderType::Limit);
}

TEST_F(TestOrders, Signals) {
    go.env->initialize_env();
    ASSERT_EQ(go.env->signals_normal_cur.size(), 0);
    strategy->buy(100, TICKER);
    ASSERT_EQ(go.env->signals_normal_cur.size(), 1);

    ASSERT_EQ(go.env->signals_pending_cur.size(), 0);
    strategy->buy(100, TICKER, 0, 0, 0, 0, 0, 0, 20, 0);
    ASSERT_EQ(go.env->signals_pending_cur.size(), 1);

    ASSERT_EQ(go.env->signals_cancel_tst_cur.size(), 0);
    strategy->cancel_tst(TICKER, "long", true);
    ASSERT_EQ(go.env->signals_cancel_tst_cur.size(), 1);

    ASSERT_EQ(go.env->signals_cancel_pending_cur.size(), 0);
    strategy->cancel_pending(TICKER, "long", 10);
    ASSERT_EQ(go.env->signals_cancel_pending_cur.size(), 1);
}

TEST_F(TestOrders, Cancel_Pending_Order) {
    go.env->initialize_env();
    strategy->buy(100, TICKER, 0, 0, 0, 0, 0, 0, 20, 0);
    strategy->buy(100, TICKER, 0, 0, 0, 0, 0, 0, 10, 0);
    strategy->buy(100, TICKER, 0, 0, 0, 0, 0, 0, 2, 0);
    test_cancel_pending_order("long");

    go.env->initialize_env();
    strategy->sell(100, TICKER, 20, 0);
    strategy->sell(100, TICKER, 10, 0);
    strategy->sell(100, TICKER, 2, 0);
    test_cancel_pending_order("long");

    go.env->initialize_env();
    strategy->shortsell(100, TICKER, 0, 0, 0, 0, 0, 0, 20, 0);
    strategy->shortsell(100, TICKER, 0, 0, 0, 0, 0, 0, 10, 0);
    strategy->shortsell(100, TICKER, 0, 0, 0, 0, 0, 0, 2, 0);
    test_cancel_pending_order("short");

    go.env->initialize_env();
    strategy->cover(100, TICKER, 20, 0);
    strategy->cover(100, TICKER, 10, 0);
    strategy->cover(100, TICKER, 2, 0);
    test_cancel_pending_order("short");
}

TEST_F(TestOrders, Cancel_TST_Order) {
    go.env->initialize_env();

    strategy->buy(100, TICKER, 30, 0, 0, 0, 0, 0);
    test_cancel_tst_order("long", true, false, false);
    strategy->buy(100, TICKER, 0, 0.01, 0, 0, 0, 0);
    test_cancel_tst_order("long", true, false, false);
    strategy->buy(100, TICKER, 0, 0, 30, 0, 0, 0);
    test_cancel_tst_order("long", false, true, false);
    strategy->buy(100, TICKER, 0, 0, 0, 0.01, 0, 0);
    test_cancel_tst_order("long", false, true, false);
    strategy->buy(100, TICKER, 0, 0, 0, 0, 30, 0);
    test_cancel_tst_order("long", false, false, true);
    strategy->buy(100, TICKER, 0, 0, 0, 0, 0, 0.01);
    test_cancel_tst_order("long", false, false, true);

    strategy->shortsell(100, TICKER, 30, 0, 0, 0, 0, 0);
    test_cancel_tst_order("short", true, false, false);
    strategy->shortsell(100, TICKER, 0, 0.01, 0, 0, 0, 0);
    test_cancel_tst_order("short", true, false, false);
    strategy->shortsell(100, TICKER, 0, 0, 30, 0, 0, 0);
    test_cancel_tst_order("short", false, true, false);
    strategy->shortsell(100, TICKER, 0, 0, 0, 0.01, 0, 0);
    test_cancel_tst_order("short", false, true, false);
    strategy->shortsell(100, TICKER, 0, 0, 0, 0, 30, 0);
    test_cancel_tst_order("short", false, false, true);
    strategy->shortsell(100, TICKER, 0, 0, 0, 0, 0, 0.01);
    test_cancel_tst_order("short", false, false, true);
}
