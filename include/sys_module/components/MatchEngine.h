#include "DataType.h"
#include "OP_DECLARE.h"

#pragma once

OP_NAMESPACE_START

class Environment;
class TradeLogGenerator;

class MatchEngine {
  public:
    MatchEngine();
    Environment *env;
    map<string, PtrBox<MarketOrderPtr>> long_log_pure;
    map<string, PtrBox<MarketOrderPtr>> long_log_with_trigger;
    map<string, PtrBox<MarketOrderPtr>> short_log_pure;
    map<string, PtrBox<MarketOrderPtr>> short_log_with_trigger;

    PtrBox<MarketOrderPtr> finished_log;
    unique_ptr<TradeLogGenerator> log_generator;
    bool left_trade_settled = false;

    template <typename T>
    void _append_finished(T &buy_order,
                          MarketOrderPtr &sell_order,
                          const double size);

    void _search_father(MarketOrderPtr &order,
                        vector<MarketOrderPtr> &log_with_trigger);
    void _del_in_mkt_dict(const int mkt_id);
    void _change_order_size_in_pending_mkt_dict(const int mkt_id,
                                                const double track_size);
    void _pair_one_by_one(PtrBox<MarketOrderPtr> &order_list,
                          double sell_size,
                          MarketOrderPtr &order,
                          const bool counteract = false);
    void _pair_order(const string &long_or_short,
                     MarketOrderPtr &order);
    void match_order(MarketOrderPtr &order);
    void append_left_trade_to_log();
    void settle_left_trade(MarketOrderPtr &unfinished_order,
                           const double size);
};

OP_NAMESPACE_END
