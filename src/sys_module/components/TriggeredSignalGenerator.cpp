#include "../../Environment.h"
#include "../../utils/utils.h"
#include "TriggeredSignalGenerator.h"

namespace sys {

template <typename T>
void TriggeredSignalGenerator::generate_bare_signal(const T &order) {
    SignalByTrigger(
        order.get_order_type(),
        order.mkt_id,
        order.trigger_key,
        order.target_price, // execute_price
        order.first_cur_price,
        order.difference,
        order.strategy_name,
        order.get_action_type(),
        order.size,
        order.ticker, 0, 0, 0, 0, 0, 0, 0);
};

template <typename T>
void TriggeredSignalGenerator::generate_full_signal(const T &order) {
    SignalByTrigger(
        order.get_order_type(),
        order.mkt_id,
        order.trigger_key,
        order.target_price,
        order.first_cur_price,
        order.difference,
        order.strategy_name,
        order.get_action_type(),
        order.size,
        order.ticker,
        order.signal_info["price"],
        order.signal_info["takeprofit"],
        order.signal_info["takeprofit_pct"],
        order.signal_info["stoploss"],
        order.signal_info["stoploss_pct"],
        order.signal_info["trailingstop"],
        order.signal_info["trailingstop_pct"]);
};

template <typename T>
void TriggeredSignalGenerator::generate_triggered_signal(const T &order) {
    static Environment *env = Environment::get_instance();
    if (!utils::is_elem_in_vector(env->cur_suspended_tickers, order.ticker))
        if (order->is_triggered()) {
            if (order.is_with_mkt())
                TriggeredSignalGenerator::generate_bare_signal(order);
            TriggeredSignalGenerator::generate_full_signal(order);
        }
};

} // namespace sys
