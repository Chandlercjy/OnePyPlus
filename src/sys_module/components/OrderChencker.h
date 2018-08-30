#include "../../DataType.h"

#pragma once

namespace sys {
class MarketOrder;
class Environment;
class OrderBase;
class BrokerBase;

class SubmitOrderChecker {

  public:
    explicit SubmitOrderChecker(Cash_func_ptr_type cash_func_ptr);
    Environment *env;

    void run();
    Cash_func_ptr_type required_cash_func;

    double cash_acumu = 0;
    map<string, int> plong_acumu;
    map<string, int> pshort_acumu;

  private:
    double cur_cash();
    double cur_position(const shared_ptr<MarketOrder> &order);
    double required_cash(const shared_ptr<MarketOrder> &order);
    double _acumu_position(const shared_ptr<MarketOrder> &order);
    void order_pass_checker(const shared_ptr<MarketOrder> &order);
    bool _is_partial(const shared_ptr<MarketOrder> &order,
                     const double cur_pos,
                     const double acumu_pos);
    bool _lack_of_cash();
    bool _lack_of_position(const double cur_pos, const double acumu_pos);

    void _add_to_cash_cumu(const shared_ptr<MarketOrder> &order);
    void _add_to_position_cumu(const shared_ptr<MarketOrder> &order);
    void _delete_from_cash_cumu(const shared_ptr<MarketOrder> &order);
    void _delete_from_position_cumu(const shared_ptr<MarketOrder> &order);
    void _make_position_cumu_full(const shared_ptr<MarketOrder> &order);

    void _check(const OrderBox<MarketOrder> order_list);
    void _check_market_order();
    void _check_pending_order();
    void _check_cancel_order();
    void _clear_all_cur_order();
};

} // namespace sys
