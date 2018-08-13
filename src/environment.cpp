#include "Environment.h"
#include "EventEngine.h"
#include "sys_module/BrokerBase.h"
#include "sys_module/CleanerBase.h"
#include "sys_module/ReaderBase.h"
#include "sys_module/RecorderBase.h"
#include "sys_module/RiskManagerBase.h"
#include "sys_module/StrategyBase.h"
#include "sys_module/models/BarBase.h"
#include <map>
#include <string>

namespace sys {
using std::make_shared;
using std::map;
using std::string;

Environment::Environment()
    : cur_suspended_tickers(make_shared<vector<string>>()),
      readers(make_shared<map<string, ReaderBase *>>()),
      feeds(make_shared<map<string, BarBase *>>()),
      cleaners_feeds(make_shared<map<string, BarBase *>>()),
      cleaners(make_shared<map<string, CleanerBase *>>()),
      strategies(make_shared<map<string, StrategyBase *>>()),
      brokers(make_shared<map<string, BrokerBase *>>()),
      risk_managers(make_shared<map<string, RiskManagerBase *>>()),
      recorders(make_shared<map<string, RecorderBase *>>()),

      event_bus(make_shared<EventEngine>()),
      execute_on_close_or_next_open("open"),
      is_save_original(false),
      is_live_trading(false),
      is_show_today_signals(false)

          {};

} // namespace sys
