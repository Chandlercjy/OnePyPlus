#include "DataType.h"

OP_NAMESPACE_START

class Environment;

class TradeLogGenerator {
  public:
    TradeLogGenerator();
    Environment *env;

    void initialize(const string &instrument);

    shared_ptr<TradeLogStruct> make_log(MarketOrderPtr &buy_order,
                                        MarketOrderPtr &sell_order,
                                        const double size);
    shared_ptr<TradeLogStruct> settle_left_trade(
        MarketOrderPtr &unfinished_order, const double size);

  private:
    map<ActionType, string> action_type_map;
    map<OrderType, string> order_type_map;

    using make_log_func_ptr =
        shared_ptr<TradeLogStruct> (TradeLogGenerator::*)(
            MarketOrderPtr &buy_order,
            MarketOrderPtr &sell_order,
            const double size);

    using settle_left_trade_func_ptr =
        shared_ptr<TradeLogStruct> (TradeLogGenerator::*)(
            MarketOrderPtr &unfinished_order, const double size);

    make_log_func_ptr _make_log_ptr;
    settle_left_trade_func_ptr _settle_left_trade_ptr;

    shared_ptr<TradeLogStruct> _make_log_A_shares(MarketOrderPtr &buy_order,
                                                  MarketOrderPtr &sell_order,
                                                  const double size);

    shared_ptr<TradeLogStruct> _settle_left_trade_A_shares(
        MarketOrderPtr &unfinished_order, const double size);

    shared_ptr<TradeLogStruct> _make_log_Forex(MarketOrderPtr &buy_order,
                                               MarketOrderPtr &sell_order,
                                               const double size);

    shared_ptr<TradeLogStruct> _settle_left_trade_Forex(
        MarketOrderPtr &unfinished_order, const double size);
};

OP_NAMESPACE_END
