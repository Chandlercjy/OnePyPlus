#include "OP_DECLARE.h"

#pragma once

OP_NAMESPACE_START

enum class OrderType;
enum class ActionType;

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

struct SignalCancelTST {
    const int id;
    const string datetime;
    const string strategy_name;
    const ActionType action_type;
    const string ticker;
    const string long_or_short;

    const bool takeprofit;
    const bool stoploss;
    const bool trailingstop;

};

struct SignalCancelPending {
    const int id;
    const string datetime;
    const string strategy_name;
    const ActionType action_type;
    const string ticker;
    const string long_or_short;

    const double below_price;
    const double above_price;

};

OP_NAMESPACE_END
