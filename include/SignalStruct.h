#include "OP_DECLARE.h"

#pragma once

enum class ActionType;

OP_NAMESPACE_START

struct SignalNormalStruct {
    const int id;
    const string datetime;
    const string strategy_name;
    const ActionType action_type;
    const string ticker;
    const double size;
    const double takeprofit;
    const double takeprofit_pct;
    const double stoploss;
    const double stoploss_pct;
    const double trailingstop;
    const double trailingstop_pct;
};

struct SignalForPendingStruct {
    const int id;
    const string datetime;
    const string strategy_name;
    const ActionType action_type;
    const string ticker;
    const double size;
    const double takeprofit;
    const double takeprofit_pct;
    const double stoploss;
    const double stoploss_pct;
    const double trailingstop;
    const double trailingstop_pct;

    const double price;
};

struct SignalByTriggerStruct {
    const int id;
    const string datetime;
    const string strategy_name;
    const ActionType action_type;
    const string ticker;
    const double size;
    const double takeprofit;
    const double takeprofit_pct;
    const double stoploss;
    const double stoploss_pct;
    const double trailingstop;
    const double trailingstop_pct;

    const int mkt_id;
    const string trigger_key;
    const OrderType by_order_type;
    const double execute_price;
    const double cur_price_when_triggered;
    const double parent_order_difference;
};

OP_NAMESPACE_END
