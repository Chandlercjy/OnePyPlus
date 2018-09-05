#include "OP_DECLARE.h"

#pragma once

OP_NAMESPACE_START

enum class OrderType;
enum class OrderStatus;
enum class ActionType;

struct MarketOrderStruct {
    MarketOrderStruct(
        const int order_id,
        const string &strategy_name,
        const string &ticker,
        double size,
        const double cur_price_when_triggered,
        const ActionType &action_type,
        const OrderType &order_type,
        const string &long_or_short,
        const string &execute_time,
        OrderStatus _status,
        const int mkt_id,
        const string &trading_date,
        const double execute_price,
        const bool father_mkt_id,
        const OrderType &by_signal_type)
        : order_id(order_id),
          strategy_name(strategy_name),
          ticker(ticker),
          size(size),
          cur_price_when_triggered(cur_price_when_triggered),
          action_type(action_type),
          order_type(order_type),
          long_or_short(long_or_short),
          execute_time(execute_time),
          _status(_status),
          mkt_id(mkt_id),
          trading_date(trading_date),
          execute_price(execute_price),
          father_mkt_id(father_mkt_id),
          by_signal_type(by_signal_type){};

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

    //独有
    const int mkt_id;
    const string trading_date;
    const double execute_price;
    const bool father_mkt_id;
    const OrderType by_signal_type;

    void set_status(const OrderStatus &value);
    OrderStatus get_status();
};

struct LimitOrderStruct {
    LimitOrderStruct(
        const int order_id,
        const string &strategy_name,
        const string &ticker,
        double size,
        const double cur_price_when_triggered,
        const ActionType action_type,
        const OrderType order_type,
        const string &long_or_short,
        const string &execute_time,
        const OrderStatus &_status,
        const string &trigger_key,
        const bool target_below,
        const bool is_with_mkt)
        : order_id(order_id),
          strategy_name(strategy_name),

          ticker(ticker),
          size(size),

          cur_price_when_triggered(cur_price_when_triggered),
          action_type(action_type),
          order_type(order_type),
          long_or_short(long_or_short),
          execute_time(execute_time),

          _status(_status),
          trigger_key(trigger_key),
          target_below(target_below),
          is_with_mkt(is_with_mkt){};

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
    StopOrderStruct(
        const int order_id,
        const string &strategy_name,

        const string &ticker,
        const double size,

        const double cur_price_when_triggered,
        const ActionType &action_type,
        const OrderType &order_type,
        const string &long_or_short,
        const string &execute_time,

        const OrderStatus &_status,
        const string &trigger_key,
        const bool target_below,
        const bool is_with_mkt)
        : order_id(order_id),
          strategy_name(strategy_name),
          ticker(ticker),
          size(size),
          cur_price_when_triggered(cur_price_when_triggered),
          action_type(action_type),
          order_type(order_type),
          long_or_short(long_or_short),
          execute_time(execute_time),
          _status(_status),
          trigger_key(trigger_key),
          target_below(target_below),
          is_with_mkt(is_with_mkt){};

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
    TrailingStopOrderStruct(
        const int order_id,
        const string &strategy_name,
        const string &ticker,
        const double size,
        const double cur_price_when_triggered,
        const ActionType &action_type,
        const OrderType &order_type,
        const string &long_or_short,
        const string &execute_time,
        const OrderStatus &_status,
        const string &trigger_key,
        const bool target_below,
        const bool is_with_mkt)
        : order_id(order_id),
          strategy_name(strategy_name),
          ticker(ticker),
          size(size),
          cur_price_when_triggered(cur_price_when_triggered),
          action_type(action_type),
          order_type(order_type),
          long_or_short(long_or_short),
          execute_time(execute_time),
          _status(_status),
          trigger_key(trigger_key),
          target_below(target_below),
          is_with_mkt(is_with_mkt){};

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

struct CancelTSTOrderStruct {

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

struct CancelPendingOrderStruct {

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
