#include "DataType.h"

OP_NAMESPACE_START
class Environment;

class TradeLogGenerator {
  public:
    TradeLogGenerator();
    Environment *env;

    template <typename T>
    shared_ptr<TradeLogStruct> make_log(shared_ptr<T> &buy_order,
                                        MarketOrderPtr &sell_order,
                                        const double size);

    shared_ptr<TradeLogStruct> settle_left_trade(
        MarketOrderPtr &unfinished_order, const double size);

  private:
    map<ActionType, string> action_type_map;
    map<OrderType, string> order_type_map;
};

OP_NAMESPACE_END
