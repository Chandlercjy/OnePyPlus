#include <string>
#include <vector>

#include "config.h"

#pragma once

namespace sys {

enum class EVENT;
class MarketMaker;
class PendingOrderChecker;
class Environment;

} // namespace sys

namespace op {
using std::shared_ptr;
using std::string;
using std::vector;

class OnePiece {
  public:
    OnePiece();
    sys::Environment *env;
    void sunny(const bool &show_summary = true); // 主循环
    void initialize_trading_system();
    void set_date(const string &fromdate,
                  const string &todate,
                  const string &frequency,
                  const string &instrument);

  private:
    vector<sys::SingleLoop> _event_loop;
    const shared_ptr<sys::MarketMaker> _market_maker;
    const shared_ptr<sys::PendingOrderChecker> _pending_order_checker;

    void output_summary(){};
    void _run_event_loop(const sys::EVENT &event);
    bool _event_is_executed(const sys::EVENT &cur_event,
                            sys::SingleLoop &single_loop) const;
    void _reset_all_counter() const;
    void _pre_initialize_trading_system();
};
} // namespace op
