#include "../../DataType.h"

#pragma once

class OrderBase;

namespace sys {
class MarketOrder;
using CashFuncPtrType = double (*)(const MarketOrder &order);

class SubmitOrderChecker {

  public:
    explicit SubmitOrderChecker(CashFuncPtrType required_cash_func);
    CashFuncPtrType required_cash_func;

    void run();

  private:
    double cur_cash();
    double cur_position(const MarketOrder &order);
    double required_cash(const MarketOrder &order);
    double _acumu_position(const MarketOrder &order);
    double order_pass_checker(const MarketOrder &order);
    bool _is_partial(const MarketOrder &order,
                     const double cur_pos,
                     const double acumu_pos);
    bool _lack_of_cash();
    bool _lack_of_position(const double cur_pos, const double acumu_pos);

    void _add_to_cash_cumu(const MarketOrder &order);
    void _add_to_position_cumu(const MarketOrder &order);
    void _delete_from_cash_cumu(const MarketOrder &order);
    void _delete_from_position_cumu(const MarketOrder &order);
    void _make_position_cumu_full(const MarketOrder &order);

    void _check(const OrderBox<OrderBase> order_list);
    void _check_market_order();
    void _check_pending_order();
    void _check_cancel_order();
    void _clear_all_cur_order();
};

} // namespace sys
