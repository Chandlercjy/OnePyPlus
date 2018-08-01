#pragma once
#include "config.h"
#include "environment.h"

class OnePiece {
  public:
    Environment *env = nullptr;

    OnePiece() : env(Environment::getInstance()){};
    void sunny(const bool &show_summary = true); // 主循环
    void initialize_trading_system();

  private:
    void output_summary(){};
    void _run_event_loop(const EVENT &event);
    bool _event_is_executed(const EVENT &cur_event,
                            const config::SingleLoop &single_loop);
    void _reset_all_counter();
    void _pre_initialize_trading_system();
};
