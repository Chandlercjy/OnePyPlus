#include "Environment.h"
#include "sys_module/RecorderBase.h"
#include "sys_module/models/GeneralOrder.h"
#include "sys_module/models/OrderBase.h"
#include "sys_module/models/SeriesBase.h"

OP_NAMESPACE_START

RecorderBase::RecorderBase()
    : env(Environment::get_instance()){};

void RecorderBase::run() {
    _record_order();
};

void RecorderBase::update(const bool &order_executed) {
    market_value->update_barly(order_executed);
    holding_pnl->update_barly(order_executed);
    margin->update_barly();
    _update_balance(env->sys_date);
    _update_cash(env->sys_date);
};

void RecorderBase::_update_balance(const string &trading_date) {
    auto total_realized_pnl = realized_pnl->total_value();
    auto total_holding_pnl = holding_pnl->total_value();
    auto total_commission = commission->total_value();
    auto new_balance = initial_cash + total_realized_pnl +
                       total_holding_pnl - total_commission;

    balance->push_back(SeriesStruct{trading_date, new_balance});
};

void RecorderBase::_record_order() {

    for (auto &order : env->orders_mkt_submitted_cur) {
        auto ticker = order->ticker;
        auto long_or_short = order->long_or_short;
        auto size = order->size;
        auto execute_price = order->execute_price;
        auto action_type = order->get_action_type();

        auto last_position = position->latest(ticker, long_or_short);
        auto last_avg_price = avg_price->latest(ticker, long_or_short);
        auto last_commission = commission->latest(ticker, long_or_short);
        position->update_order(ticker, size, action_type,
                               last_position, long_or_short);
        auto new_position = position->latest(ticker, long_or_short);

        avg_price->update_order(ticker,
                                size,
                                execute_price,
                                last_position,
                                last_avg_price,
                                new_position,
                                long_or_short);

        commission->update_order(ticker,
                                 size,
                                 execute_price,
                                 action_type,
                                 last_commission,
                                 long_or_short);
        realized_pnl->update_order(ticker,
                                   size,
                                   execute_price,
                                   action_type,
                                   last_avg_price,
                                   long_or_short);
        margin->update_order(ticker, long_or_short);
        //match_engine.match_order(order)
        update(true);
    }
};

template <typename T>
void RecorderBase::save_to_env(const T *self_ptr, const string &name) {
    env->recorders[name] = make_shared<T>(*self_ptr); //TODO:设置名字
    env->recorder = env->recorders[name];
}

OP_NAMESPACE_END

