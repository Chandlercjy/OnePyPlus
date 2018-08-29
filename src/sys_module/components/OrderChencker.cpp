#include "../models/GeneralOrder.h"
#include "OrderChencker.h"

namespace sys {

SubmitOrderChecker::SubmitOrderChecker(CashFuncPtrType required_cash_func)
    : required_cash_func(required_cash_func){};

//double SubmitOrderChecker::cur_cash() { return 999; }; //TODO
//double SubmitOrderChecker::cur_position(const MarketOrder &order){};
//double SubmitOrderChecker::required_cash(const MarketOrder &order){};
//double SubmitOrderChecker::_acumu_position(const MarketOrder &order){};
//double SubmitOrderChecker::order_pass_checker(const MarketOrder &order){};
//bool SubmitOrderChecker::_is_partial(const MarketOrder &order,
//const double cur_pos,
//const double acumu_pos){};
//bool SubmitOrderChecker::_lack_of_cash(){};
//bool SubmitOrderChecker::_lack_of_position(const double cur_pos, const double acumu_pos){};

void SubmitOrderChecker::_add_to_cash_cumu(const MarketOrder &order){};
void SubmitOrderChecker::_add_to_position_cumu(const MarketOrder &order){};
void SubmitOrderChecker::_delete_from_cash_cumu(const MarketOrder &order){};
void SubmitOrderChecker::_delete_from_position_cumu(const MarketOrder &order){};
void SubmitOrderChecker::_make_position_cumu_full(const MarketOrder &order){};

void SubmitOrderChecker::_check(const OrderBox<OrderBase> order_list){};
void SubmitOrderChecker::_check_market_order(){};
void SubmitOrderChecker::_check_pending_order(){};
void SubmitOrderChecker::_check_cancel_order(){};
void SubmitOrderChecker::_clear_all_cur_order(){};

} // namespace sys
