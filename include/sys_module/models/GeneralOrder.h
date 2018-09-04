#include "BarBase.h"
#include "CancelOrderBase.h"
#include "OP_DECLARE.h"
#include "OrderBase.h"
#include "PendingOrderBase.h"
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
    const ActionType get_action_type() const override;
    const OrderType get_order_type() const override;

  private:
    const string _set_long_or_short();

    const int _set_father_mkt_id(const shared_ptr<SignalByTrigger> &signal);

    const ActionType _action_type;
    const OrderType _order_type;
};

class LimitBuyOrder : public PendingOrderBase {
  public:
    using PendingOrderBase::PendingOrderBase;
    const ActionType get_action_type() const override;
    const OrderType get_order_type() const override;
    const bool target_below() const override;
};

class LimitSellOrder : public PendingOrderBase {
  public:
    using PendingOrderBase::PendingOrderBase;
    const ActionType get_action_type() const override;
    const OrderType get_order_type() const override;
    const bool target_below() const override;
};

class StopBuyOrder : public PendingOrderBase {
  public:
    using PendingOrderBase::PendingOrderBase;
    const ActionType get_action_type() const override;
    const OrderType get_order_type() const override;

    const bool target_below() const override;
};

class StopSellOrder : public PendingOrderBase {
  public:
    using PendingOrderBase::PendingOrderBase;
    const ActionType get_action_type() const override;
    const OrderType get_order_type() const override;

    const bool target_below() const override;
};

class LimitShortOrder : public PendingOrderBase {
  public:
    using PendingOrderBase::PendingOrderBase;
    const ActionType get_action_type() const override;
    const OrderType get_order_type() const override;

    const bool target_below() const override;
};

class LimitCoverOrder : public PendingOrderBase {
  public:
    using PendingOrderBase::PendingOrderBase;
    const ActionType get_action_type() const override;
    const OrderType get_order_type() const override;

    const bool target_below() const override;
};

class StopShortOrder : public PendingOrderBase {
  public:
    using PendingOrderBase::PendingOrderBase;
    const ActionType get_action_type() const override;
    const OrderType get_order_type() const override;

    const bool target_below() const override;
};

class StopCoverOrder : public PendingOrderBase {
  public:
    using PendingOrderBase::PendingOrderBase;
    const ActionType get_action_type() const override;
    const OrderType get_order_type() const override;

    const bool target_below() const override;
};

class TrailingStopSellOrder : public TrailingOrderBase {
  public:
    using TrailingOrderBase::TrailingOrderBase;
    const ActionType get_action_type() const override;
    const OrderType get_order_type() const override;

    const bool target_below() const override;
};

class TrailingStopCoverOrder : public TrailingOrderBase {
  public:
    using TrailingOrderBase::TrailingOrderBase;
    const ActionType get_action_type() const override;
    const OrderType get_order_type() const override;

    const bool target_below() const override;
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
