#include "DataType.h"
#include "OP_DECLARE.h"

#pragma once

OP_NAMESPACE_START

class MarketOrder;
class Environment;
class OrderBase;
class BrokerBase;
enum class ActionType;

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
    double cur_position(const string &ticker,
                        const ActionType &action_type);
    double required_cash(const MarketOrderPtr &order);
    double _acumu_position(const string &ticker,
                           const ActionType &action_type);
    void order_pass_checker(const MarketOrderPtr &order);
    bool _is_partial(const MarketOrderPtr &order,
                     const double cur_pos,
                     const double acumu_pos);
    bool _lack_of_cash();
    bool _lack_of_position(const double cur_pos, const double acumu_pos);

    void _add_to_cash_cumu(const MarketOrderPtr &order);
    void _add_to_position_cumu(const MarketOrderPtr &order);
    void _delete_from_cash_cumu(const MarketOrderPtr &order);
    void _delete_from_position_cumu(const MarketOrderPtr &order);
    void _make_position_cumu_full(const string &ticker,
                                  const ActionType &action_type);

    void _check(const PtrBox<MarketOrderPtr> order_list);
    void _check_market_order();
    void _check_pending_order();
    void _check_cancel_order();
    void _clear_all_cur_order();
};

OP_NAMESPACE_END
