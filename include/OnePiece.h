#include "OP_DECLARE.h"
#include "config.h"

#pragma once

OP_NAMESPACE_START

enum class EVENT;
class MarketMaker;
class PendingOrderChecker;
class Environment;

class OnePiece {
  public:
    OnePiece();
    Environment *env;
    const shared_ptr<MarketMaker> market_maker;
    const shared_ptr<PendingOrderChecker> _pending_order_checker;

    void sunny(); // 主循环
    void initialize_trading_system();
    void set_date(const string &fromdate,
                  const string &todate,
                  const string &frequency);
    void set_stock_backtest(const double initial_cash,
                            const double comm,
                            const double comm_pct,
                            const double margin_rate);

    void set_forex_backtest(const double initial_cash,
                            const double margin_rate);

  private:
    vector<SingleLoop> _event_loop;

    void _run_event_loop(const EVENT &event);
    bool _event_is_executed(const EVENT &cur_event,
                            SingleLoop &single_loop) const;
    void _reset_all_counter() const;
    void _pre_initialize_trading_system();
};

OP_NAMESPACE_END
