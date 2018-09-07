#include "BarBase.h"
#include "CancelOrderBase.h"
#include "OP_DECLARE.h"
#include "OrderBase.h"
#include "PendingOrder.h"
#include "TrailingOrderBase.h"
#include <exception>

#pragma once

OP_NAMESPACE_START

enum class ActionType;
enum class OrderType;
class Signal;
class SignalByTrigger;

class MarketOrder : public OrderBase {
  public:
    MarketOrder(const shared_ptr<Signal> &signal, const int mkt_id);
    MarketOrder(const shared_ptr<SignalByTrigger> &signal, const int mkt_id);

    const double execute_price;
    const bool father_mkt_id;
    const string long_or_short;

    const bool is_pure();
    const ActionType action_type;
    const OrderType order_type;

  private:
    const string _set_long_or_short();

    const int _set_father_mkt_id(const shared_ptr<SignalByTrigger> &signal);
};

class CancelTSTOrder : public CancelOrderBase {
  public:
    explicit CancelTSTOrder(const shared_ptr<SignalCancelTST> &signal);

    const bool takeprofit;
    const bool stoploss;
    const bool trailingstop;
    const bool is_target(const string &trigger_key) override;
    const bool is_target(const double target_price) override { throw std::logic_error("Never raised"); };

  private:
    void _save_signal_info() override;
};

class CancelPendingOrder : public CancelOrderBase {
  public:
    explicit CancelPendingOrder(const shared_ptr<SignalCancelPending> &signal);

    const double below_price;
    const double above_price;
    const bool is_target(const string &trigger_key) override { throw std::logic_error("Never raised"); };
    const bool is_target(const double target_price) override;

  private:
    void _save_signal_info() override;
};

OP_NAMESPACE_END
