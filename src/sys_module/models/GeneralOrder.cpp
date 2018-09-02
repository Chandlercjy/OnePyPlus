#include "Constants.h"
#include "sys_module/models/CancelOrderBase.h"
#include "sys_module/models/GeneralOrder.h"
#include "sys_module/models/OrderBase.h"
#include "sys_module/models/PendingOrderBase.h"
#include "sys_module/models/SignalCancel.h"
#include "sys_module/models/TrailingOrderBase.h"
#include "utils/utils.h"

namespace op {

MarketOrder::MarketOrder(const shared_ptr<Signal> &signal, const int mkt_id)
    : OrderBase(signal, mkt_id),
      execute_price(_first_cur_price),
      father_mkt_id(-1),
      long_or_short(_set_long_or_short()),
      _action_type(signal->action_type),
      _order_type(OrderType::Market){};

MarketOrder::MarketOrder(const shared_ptr<SignalByTrigger> &signal,
                         const int mkt_id)
    : OrderBase(signal, mkt_id),
      execute_price(_first_cur_price),
      father_mkt_id(_set_father_mkt_id(signal)),
      long_or_short(_set_long_or_short()),
      _action_type(signal->action_type),
      _order_type(OrderType::Market){};

const bool MarketOrder::is_pure() {
    return !utils::Stl::is_elem_in_map_key(env->orders_child_of_mkt_dict, mkt_id);
}
const ActionType MarketOrder::get_action_type() const { return _action_type; };
const OrderType MarketOrder::get_order_type() const { return _order_type; };
const string MarketOrder::_set_long_or_short() {
    if (_action_type == ActionType::Buy || _action_type == ActionType::Sell)
        return "long";
    return "short";
};

const int MarketOrder::_set_father_mkt_id(const shared_ptr<SignalByTrigger> &signal) {
    return signal->mkt_id;
};

const bool LimitBuyOrder::target_below() const { return true; };
const ActionType LimitBuyOrder::get_action_type() const { return ActionType::Buy; };
const OrderType LimitBuyOrder::get_order_type() const { return OrderType::Limit; };

const bool LimitSellOrder::target_below() const { return false; };
const ActionType LimitSellOrder::get_action_type() const { return ActionType::Sell; };
const OrderType LimitSellOrder::get_order_type() const { return OrderType::Limit; };

const bool StopBuyOrder::target_below() const { return false; };
const ActionType StopBuyOrder::get_action_type() const { return ActionType::Buy; };
const OrderType StopBuyOrder::get_order_type() const { return OrderType::Stop; };

const bool StopSellOrder::target_below() const { return true; };
const ActionType StopSellOrder::get_action_type() const { return ActionType::Sell; };
const OrderType StopSellOrder::get_order_type() const { return OrderType::Stop; };

const bool LimitShortOrder::target_below() const { return false; };
const ActionType LimitShortOrder::get_action_type() const { return ActionType::Short; };
const OrderType LimitShortOrder::get_order_type() const { return OrderType::Limit; };

const bool LimitCoverOrder::target_below() const { return true; };
const ActionType LimitCoverOrder::get_action_type() const { return ActionType::Cover; };
const OrderType LimitCoverOrder::get_order_type() const { return OrderType::Limit; };

const bool StopShortOrder::target_below() const { return true; };
const ActionType StopShortOrder::get_action_type() const { return ActionType::Short; };
const OrderType StopShortOrder::get_order_type() const { return OrderType::Stop; };

const bool StopCoverOrder::target_below() const { return false; };
const ActionType StopCoverOrder::get_action_type() const { return ActionType::Cover; };
const OrderType StopCoverOrder::get_order_type() const { return OrderType::Stop; };

const bool TrailingStopSellOrder::target_below() const { return false; };
const ActionType TrailingStopSellOrder::get_action_type() const { return ActionType::Sell; };
const OrderType TrailingStopSellOrder::get_order_type() const { return OrderType::Trailing_stop; };

const bool TrailingStopCoverOrder::target_below() const { return false; };
const ActionType TrailingStopCoverOrder::get_action_type() const { return ActionType::Cover; };
const OrderType TrailingStopCoverOrder::get_order_type() const { return OrderType::Trailing_stop; };

CancelTSTOrder::CancelTSTOrder(const shared_ptr<SignalCancelTST> &signal)
    : CancelOrderBase(signal),
      takeprofit(signal->takeprofit),
      stoploss(signal->stoploss),
      trailingstop(signal->trailingstop) {
    _save_signal_info();
};

void CancelTSTOrder::_save_signal_info() {
    signal_info["takeprofit"] = takeprofit;
    signal_info["stoploss"] = stoploss;
    signal_info["trailingstop"] = trailingstop;
};

const bool CancelTSTOrder::is_target(const string &trigger_key) {
    return signal_info[trigger_key];
};

CancelPendingOrder::CancelPendingOrder(const shared_ptr<SignalCancelPending> &signal)
    : CancelOrderBase(signal),
      below_price(signal->below_price),
      above_price(signal->above_price) {
    _save_signal_info();
};

void CancelPendingOrder::_save_signal_info() {
    signal_info["below_price"] = below_price;
    signal_info["above_price"] = above_price;
};

const bool CancelPendingOrder::is_target(const double target_price) {
    if (below_price != 0)
        return target_price <= below_price;
    else if (above_price != 0)
        return target_price <= above_price;
    throw std::logic_error("Never raised");
    return false;
};

} // namespace op
