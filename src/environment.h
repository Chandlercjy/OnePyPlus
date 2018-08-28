
#include <map>
#include <string>
#include <vector>

#pragma once

namespace sys {
using std::map;
using std::shared_ptr;
using std::string;
using std::vector;

class ReaderBase;
class BarBase;
class BarBase;
class CleanerBase;
class StrategyBase;
class BrokerBase;
class RiskManagerBase;
class RecorderBase;
class EventEngine;
class Signal;
class SignalForPending;
class SignalByTrigger;
class SignalCancel;
class SignalCancelTST;
class SignalCancelPending;
class OrderBase;
class PendingOrderBase;
class CancelOrderBase;

class Environment {
  public:
    string instrument = "A_shares";
    string sys_date = "2018-01-11";
    string sys_frequency = "D";

    const string fromdate = "2018-01-12";
    const string todate = "2018-03-19";
    const vector<string> tickers;
    vector<string> cur_suspended_tickers;
    map<const string, vector<string>> suspended_tickers_record;

    map<string, shared_ptr<ReaderBase>> readers;
    map<string, shared_ptr<BarBase>> feeds;
    map<string, shared_ptr<BarBase>> cleaners_feeds;
    map<string, shared_ptr<CleanerBase>> cleaners;
    map<string, shared_ptr<StrategyBase>> strategies;
    map<string, shared_ptr<BrokerBase>> brokers;
    map<string, shared_ptr<RiskManagerBase>> risk_managers;
    map<string, shared_ptr<RecorderBase>> recorders;
    shared_ptr<RecorderBase> recorder = nullptr; // type: op.RecorderBase

    //vector<shared_ptr<Signal>> signals_normal;  // 保存最原始的所有信号
    //vector<shared_ptr<Signal>> signals_trigger; // 保存最原始的所有挂单信号
    //vector<shared_ptr<Signal>> signals_cancel;  // 保存最原始的所有挂单信号
    //vector< > orders_mkt_original ;    // 保存最原始的所有订单信号
    //vector< > orders_cancel_original ; // 保存最原始的所有订单信号

    vector<shared_ptr<Signal>> signals_normal_cur;                      // 动态地临时信号，会不断刷新
    vector<shared_ptr<SignalForPending>> signals_pending_cur;           // 动态地临时信号，会不断刷新
    vector<shared_ptr<SignalByTrigger>> signals_trigger_cur;            // 动态地临时信号，会不断刷新
    vector<shared_ptr<SignalCancelTST>> signals_cancel_tst_cur;         // 动态地临时信号，会不断刷新
    vector<shared_ptr<SignalCancelPending>> signals_cancel_pending_cur; // 动态地临时信号，会不断刷新

    vector<shared_ptr<OrderBase>> orders_mkt_normal_cur;              // 动态地保存当前订单, 会不断刷新
    map<int, vector<shared_ptr<OrderBase>>> orders_child_of_mkt_dict; // 动态地保存跟随市价单的挂单
    vector<shared_ptr<OrderBase>> orders_mkt_absolute_cur;            // 动态地保存触发的挂单并成交信息，会不断刷新
    vector<shared_ptr<OrderBase>> orders_mkt_submitted_cur;           // 动态地保存成交单，会不断刷新

    vector<shared_ptr<PendingOrderBase>> orders_pending; // 动态地保存挂单,触发会删除

    vector<shared_ptr<CancelOrderBase>> orders_cancel_cur;       // 动态地保存撤单，会不断刷新
    vector<shared_ptr<CancelOrderBase>> orders_cancel_submitted; // 动态地保存撤单，会不断刷新

    //string logger = logging.getLogger("OnePy");
    std::shared_ptr<EventEngine> event_engine; //看看能不能设成会报错的指针
    //string event_loop = "";
    //string calendar = "";  // type:op.Calendar
    //string bar_class = ""; // type:op.BarBase
    //string cache = {};

    string execute_on_close_or_next_open;
    bool is_save_original; // 是否保存原始信号的开关
    bool is_live_trading;
    bool is_show_today_signals; // 是否显示当前最新信号的开关

    void initialize_env();

  public:
    static Environment *get_instance() noexcept {

        static Environment instance;
        return &instance;
    };

  private:
    struct Object_Creator {
        Object_Creator() {
            Environment::get_instance();
        }
    };
    static Object_Creator _object_creator;
    Environment() noexcept;   // ctor hidden
    ~Environment() = default; // dtor hidden
};
} // namespace sys
