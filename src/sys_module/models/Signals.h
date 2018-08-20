#include "../../Constants.h"

#pragma once

class Signal{

    public:

    string strategy_name: str
    ActionType action_type
    double size: double
    string ticker: str
    double takeprofit: float = None
    double takeprofit_pct: float = None
    double stoploss: float = None
    double stoploss_pct: float = None
    double trailingstop: float = None
    double trailingstop_pct: float = None
    double price: float = None
    double price_pct: float = None
    double mkt_id: float = None
    int signal_id: int = None

    OrderType order_type: OrderType = None

    //string datetime;

};
