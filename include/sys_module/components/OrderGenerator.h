#include "OP_DECLARE.h"

#pragma once

OP_NAMESPACE_START

class Environment;
class OrderBase;
class SignalByTrigger;
class MarketOrder;
class PendingOrderBase;

class OrderGenerator {

  public:
    OrderGenerator();
    Environment *env;
    void run();

  private:
    const double cur_price(const string &ticker);

    template <typename T>
    const bool is_buy(const T &signal);
    template <typename T>
    const bool is_sell(const T &signal);
    template <typename T>
    const bool is_short(const T &signal);
    template <typename T>
    const bool is_shortcover(const T &signal);
    template <typename T>
    const bool is_absolute_mkt(const T &signal);
    template <typename T>
    const bool is_normal_mkt(const T &signal);

    template <typename T1, typename T2>
    void _child_of_mkt(const shared_ptr<T2> &signal,
                       const int mkt_id,
                       const string &key,
                       vector<shared_ptr<PendingOrderBase>> &orders_basket);

    template <typename T>
    MarketOrderPtr _generate_mkt_order(const shared_ptr<T> &signal);

    template <typename T>
    vector<shared_ptr<PendingOrderBase>> _generate_child_of_mkt(const int mkt_id,
                                                                const shared_ptr<T> &signal);

    template <typename T>
    shared_ptr<PendingOrderBase> _generate_pending_order(const shared_ptr<T> &signal);

    void submit_mkt_order_with_child(MarketOrderPtr &mkt_order,
                                     const vector<shared_ptr<PendingOrderBase>> &orders_basket,
                                     vector<MarketOrderPtr> &orders_cur);

    void _process_mkt_signals();
    void _process_triggered_signals();
    void _process_pending_signals();
    void _process_cancel_signals();
    void _clear_current_signals_memory();
};

OP_NAMESPACE_END
