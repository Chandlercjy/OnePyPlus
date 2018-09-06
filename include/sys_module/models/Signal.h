#include "Constants.h"
#include "OP_DECLARE.h"

#pragma once

OP_NAMESPACE_START

class Environment;
class OrderBase;

class SignalBase {

  public:
    SignalBase(const map<string, double> &info,
               const string &ticker,
               const string &strategy_name,
               const ActionType &action_type);

    Environment *env;

    map<string, double> info;
    const string ticker;

    const string strategy_name;
    const ActionType action_type;

    double size();
    double price();
    double takeprofit();
    double takeprofit_pct();
    double stoploss();
    double stoploss_pct();
    double trailingstop();
    double trailingstop_pct();

    const string datetime;
};

class Signal : public SignalBase {
  public:
    Signal(const map<string, double> &info,
           const string &ticker,
           const string &strategy_name,
           const ActionType &action_type);

    const int signal_id;
};

class SignalForPending : public SignalBase {
  public:
    SignalForPending(const map<string, double> &info,
                     const string &ticker,
                     const string &strategy_name,
                     const ActionType &action_type);

    const int signal_id;
};

class SignalByTrigger : public SignalBase {
  public:
    SignalByTrigger(const map<string, double> &info,
                    const string &ticker,
                    const string &strategy_name,
                    const ActionType &action_type,
                    const OrderType &order_type,
                    const int mkt_id,
                    const string &trigger_key,
                    const double execute_price,
                    const double cur_price_when_generated,
                    const double parent_order_difference);

    const OrderType order_type;
    const int mkt_id;
    const string trigger_key;
    const double execute_price;
    const double cur_price_when_generated;
    const double parent_order_difference;

    const int signal_id; // 触发信号重新计数
};

OP_NAMESPACE_END
