#pragma once

#include <map>
#include <string>
#include <vector>

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

class Environment {
  public:
    string sys_date = "";
    //string sys_frequency = "";

    //string fromdate = "";
    //string todate = "";
    //string tickers[];
    shared_ptr<vector<string>> cur_suspended_tickers;
    //string suspended_tickers_record : defaultdict = defaultdict(list);

    //string market_maker = "";
    shared_ptr<map<string, ReaderBase *>> readers;
    shared_ptr<map<string, BarBase *>> feeds;
    shared_ptr<map<string, BarBase *>> cleaners_feeds;
    shared_ptr<map<string, CleanerBase *>> cleaners;
    shared_ptr<map<string, StrategyBase *>> strategies;
    shared_ptr<map<string, BrokerBase *>> brokers;
    shared_ptr<map<string, RiskManagerBase *>> risk_managers;
    shared_ptr<map<string, RecorderBase *>> recorders;
    //string recorder = ""; // type: op.RecorderBase

    //string signals_normal = [];         // 保存最原始的所有信号
    //string signals_trigger = [];        // 保存最原始的所有挂单信号
    //string signals_cancel = [];         // 保存最原始的所有挂单信号
    //string orders_mkt_original = [];    // 保存最原始的所有订单信号
    //string orders_cancel_original = []; // 保存最原始的所有订单信号

    //string signals_normal_cur = [];  // 动态地临时信号，会不断刷新
    //string signals_pending_cur = []; // 动态地临时信号，会不断刷新
    //string signals_trigger_cur = []; // 动态地临时信号，会不断刷新
    //string signals_cancel_cur = [];  // 动态地临时信号，会不断刷新

    //string orders_mkt_normal_cur = [];    // 动态地保存当前订单, 会不断刷新
    //string orders_child_of_mkt_dict = {}; // 动态地保存跟随市价单的挂单
    //string orders_mkt_absolute_cur = [];  // 动态地保存触发的挂单并成交信息，会不断刷新
    //string orders_mkt_submitted = [];     // 动态地保存成交单，会不断刷新

    //string orders_pending = []; // 动态地保存挂单,触发会删除

    //string orders_cancel_cur = [];       // 动态地保存撤单，会不断刷新
    //string orders_cancel_submitted = []; // 动态地保存撤单，会不断刷新

    //string logger = logging.getLogger("OnePy");
    std::shared_ptr<EventEngine> event_bus; //看看能不能设成会报错的指针
    //string event_loop = "";
    //string calendar = "";  // type:op.Calendar
    //string bar_class = ""; // type:op.BarBase
    //string cache = {};

    string execute_on_close_or_next_open;
    bool is_save_original; // 是否保存原始信号的开关
    bool is_live_trading;
    bool is_show_today_signals; // 是否显示当前最新信号的开关

  public:
    static Environment *get_instance() {

        static Environment instance;
        return &instance;
    };
    string instrument;

  private:
    struct Object_Creator {
        Object_Creator() {
            Environment::get_instance();
        }
    };
    static Object_Creator _object_creator;
    Environment();            // ctor hidden
    ~Environment() = default; // dtor hidden
};
} // namespace sys
