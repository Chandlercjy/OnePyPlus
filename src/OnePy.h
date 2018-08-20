#pragma once

#include "Environment.h"

namespace sys {

enum class EVENT;
struct SingleLoop;
class MarketMaker;

} // namespace sys

namespace op {

using namespace sys;
class OnePiece {
  public:
    OnePiece();
    sys::Environment *env;
    void sunny(const bool &show_summary = true); // 主循环
    void initialize_trading_system();

  private:
    const std::unique_ptr<MarketMaker> _market_maker;
    void output_summary(){};
    void _run_event_loop(const sys::EVENT &event) const;
    bool _event_is_executed(const sys::EVENT &cur_event,
                            sys::SingleLoop &single_loop) const;
    void _reset_all_counter() const;
    void _pre_initialize_trading_system();
};
} // namespace op
