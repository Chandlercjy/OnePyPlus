#include "Environment.h"
#include "EventEngine.h"
#include "utils/arrow.h"
#include "utils/easy_func.h"

OP_NAMESPACE_START

Environment::Environment() noexcept
    : event_engine(make_shared<EventEngine>()),
      execute_on_close_or_next_open("open"),
      is_save_original(false),
      is_live_trading(false),
      is_show_today_signals(false){};

void Environment::initialize_env() {
    const vector<string> *ticker_ptr_const;
    ticker_ptr_const = &tickers;
    auto ticker_ptr = const_cast<vector<string> *>(ticker_ptr_const);

    ticker_ptr->clear();
    cur_suspended_tickers.clear();
    suspended_tickers_record.clear();

    signals_normal_cur.clear();              // 动态地临时信号，会不断刷新
    signals_pending_cur.clear();             // 动态地临时信号，会不断刷新
    signals_trigger_cur.clear();             // 动态地临时信号，会不断刷新
    signals_cancel_tst_cur.clear();          // 动态地临时信号，会不断刷新
    signals_cancel_pending_cur.clear();      // 动态地临时信号，会不断刷新
    orders_child_of_mkt_dict.clear();        // 动态地保存跟随市价单的挂单
    orders_mkt_normal_cur.clear();           // 动态地保存当前订单, 会不断刷新
    orders_mkt_absolute_cur.clear();         // 动态地保存触发的挂单并成交信息，会不断刷新
    orders_mkt_submitted_cur.clear();        // 动态地保存成交单，会不断刷新
    orders_pending.clear();                  // 动态地保存挂单,触发会删除
    orders_cancel_tst_cur.clear();           // 动态地保存撤单，会不断刷新
    orders_cancel_pending_cur.clear();       // 动态地保存撤单，会不断刷新
    orders_cancel_tst_submitted.clear();     // 动态地保存撤单，会不断刷新
    orders_cancel_pending_submitted.clear(); // 动态地保存撤单，会不断刷新
    if (!is_live_trading) {
        auto shift_ratio = utils::Easy::get_second_ratio(sys_frequency);
        sys_date = utils::arrow::shift_seconds_to_str(fromdate, -shift_ratio);
    }
};

void Environment::save_module(const string &name,
                              const shared_ptr<ReaderBase> &value) {
    readers[name] = value;
}

void Environment::save_module(const string &name,
                              const shared_ptr<CleanerBase> &value) {
    cleaners[name] = value;
}

void Environment::save_module(const string &name,
                              const shared_ptr<StrategyBase> &value) {
    strategies[name] = value;
}

void Environment::save_module(const string &name,
                              const shared_ptr<RiskManagerBase> &value) {
    risk_managers[name] = value;
}
void Environment::save_module(const string &name,
                              const shared_ptr<BrokerBase> &value) {
    brokers[name] = value;
}
void Environment::save_module(const string &name,
                              const shared_ptr<RecorderBase> &value) {
    recorders[name] = value;
    recorder = value;
}

OP_NAMESPACE_END
