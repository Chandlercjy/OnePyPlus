#include "OP_DECLARE.h"

#pragma once

OP_NAMESPACE_START

enum class OrderType;
enum class OrderStatus;
enum class ActionType;

struct MarketOrderStruct {

    const int order_id;
    const string strategy_name;

    const string ticker;
    double size;

    const double cur_price_when_triggered;
    const ActionType action_type;
    const OrderType order_type;
    const string long_or_short;
    const string execute_time;

    OrderStatus _status;
    void set_status(const OrderStatus &value);
    OrderStatus get_status();

    //独有
    const int mkt_id;
    const string trading_date;
    const double execute_price;
    const bool father_mkt_id;
    const OrderType by_signal_type;
};

struct LimitOrderStruct {

    const int order_id;
    const string strategy_name;

    const string ticker;
    double size;

    const double cur_price_when_triggered;
    const ActionType action_type;
    const OrderType order_type;
    const string long_or_short;
    const string execute_time;

    OrderStatus _status;
    void set_status(const OrderStatus &value);
    OrderStatus get_status();
    //独有
    const string trigger_key;
    const bool target_below;
    const bool is_with_mkt;
};

struct StopOrderStruct {

    const int order_id;
    const string strategy_name;

    const string ticker;
    double size;

    const double cur_price_when_triggered;
    const ActionType action_type;
    const OrderType order_type;
    const string long_or_short;
    const string execute_time;

    OrderStatus _status;
    void set_status(const OrderStatus &value);
    OrderStatus get_status();

    //独有
    const string trigger_key;
    const bool target_below;
    const bool is_with_mkt;
};

struct TrailingStopOrderStruct {

    const int order_id;
    const string strategy_name;

    const string ticker;
    double size;

    const double cur_price_when_triggered;
    const ActionType action_type;
    const OrderType order_type;
    const string long_or_short;
    const string execute_time;

    OrderStatus _status;
    void set_status(const OrderStatus &value);
    OrderStatus get_status();

    //独有
    const string trigger_key;
    const bool target_below;
    const bool is_with_mkt;
};

struct CancelOrderTSTStruct {

    const int order_id;
    const string strategy_name;

    const string ticker;

    const double cur_price_when_triggered;
    const ActionType action_type;
    const OrderType order_type;
    const string long_or_short;
    const string execute_time;

    OrderStatus _status;
    void set_status(const OrderStatus &value);
    OrderStatus get_status();

    //独有
    const bool takeprofit;
    const bool stoploss;
    const bool trailingstop;
};

struct CancelOrderPendingStruct {

    const int order_id;
    const string strategy_name;

    const string ticker;

    const double cur_price_when_triggered;
    const ActionType action_type;
    const OrderType order_type;
    const string long_or_short;
    const string execute_time;

    OrderStatus _status;
    void set_status(const OrderStatus &value);
    OrderStatus get_status();

    //独有
    const double below_price;
    const double above_price;
};

OP_NAMESPACE_END
