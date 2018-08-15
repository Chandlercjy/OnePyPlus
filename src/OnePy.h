#pragma once

#include "Environment.h"

namespace sys {

enum class EVENT;
class SingleLoop;

} // namespace sys

namespace op {
class OnePiece {
  public:
    OnePiece() : env(sys::Environment::get_instance()){};
    sys::Environment *env;
    void sunny(const bool &show_summary = true); // 主循环
    void initialize_trading_system();

  private:
    void output_summary(){};
    void _run_event_loop(const sys::EVENT &event);
    bool _event_is_executed(const sys::EVENT &cur_event,
                            sys::SingleLoop &single_loop);
    void _reset_all_counter();
    void _pre_initialize_trading_system();

    template <typename T>
    inline void _run_modules(T &modules);
};
} // namespace op
