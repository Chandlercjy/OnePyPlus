#include "Constants.h"
#include "sys_module/models/CancelOrderBase.h"
#include "sys_module/models/GeneralOrder.h"
#include "sys_module/models/OrderBase.h"
#include "sys_module/models/PendingOrder.h"
#include "sys_module/models/SignalCancel.h"
#include "sys_module/models/TrailingOrderBase.h"
#include "utils/utils.h"

OP_NAMESPACE_START

MarketOrder::MarketOrder(const shared_ptr<Signal> &signal, const int mkt_id)
    : OrderBase(signal, mkt_id),
      execute_price(_cur_price_when_generated),
      father_mkt_id(-1),
      action_type(signal->action_type),
      long_or_short(_set_long_or_short()),
      order_type(OrderType::Market){};

MarketOrder::MarketOrder(const shared_ptr<SignalByTrigger> &signal,
                         const int mkt_id)
    : OrderBase(signal, mkt_id),
      execute_price(signal->execute_price),
      father_mkt_id(signal->mkt_id),
      action_type(signal->action_type),
      long_or_short(_set_long_or_short()),
      order_type(OrderType::Market){};

const bool MarketOrder::is_pure() {
    return !utils::Stl::is_elem_in_map_key(env->orders_child_of_mkt_dict, mkt_id);
}
const string MarketOrder::_set_long_or_short() {
    if (action_type == ActionType::Buy || action_type == ActionType::Sell)
        return "long";
    return "short";
};


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

    signal_info["takeprofit_pct"] = takeprofit;
    signal_info["stoploss_pct"] = stoploss;
    signal_info["trailingstop_pct"] = trailingstop;
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
        return target_price >= above_price;
    throw std::logic_error("Never raised");
    return false;
};

OP_NAMESPACE_END
