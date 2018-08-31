#include "OnePy.h"
#include "builtin_module/CsvReader.h"
#include "src/Environment.cpp"
#include "src/EventEngine.cpp"
#include "src/OnePy.cpp"
#include "src/builtin_module/CsvReader.cpp"
#include "src/builtin_module/backtest_stock/StockBroker.cpp"
#include "src/builtin_module/backtest_stock/StockRecorder.cpp"
#include "src/builtin_module/backtest_stock/StockSeries.cpp"
#include "src/config.cpp"
#include "src/custom_module/backtest.cpp"
#include "src/sys_module/BrokerBase.cpp"
#include "src/sys_module/CleanerBase.cpp"
#include "src/sys_module/ReaderBase.cpp"
#include "src/sys_module/RecorderBase.cpp"
#include "src/sys_module/RiskManagerBase.cpp"
#include "src/sys_module/StrategyBase.cpp"
#include "src/sys_module/components/MarketMaker.cpp"
#include "src/sys_module/components/OrderGenerator.cpp"
#include "src/sys_module/components/PendingOrderChecker.cpp"
#include "src/sys_module/components/SignalGenerator.cpp"
#include "src/sys_module/components/SubmitOrderChecker.cpp"
#include "src/sys_module/components/TriggeredSignalGenerator.cpp"
#include "src/sys_module/models/BarBase.cpp"
#include "src/sys_module/models/Calendar.cpp"
#include "src/sys_module/models/CancelOrderBase.cpp"
#include "src/sys_module/models/GeneralOrder.cpp"
#include "src/sys_module/models/OrderBase.cpp"
#include "src/sys_module/models/PendingOrderBase.cpp"
#include "src/sys_module/models/SeriesBase.cpp"
#include "src/sys_module/models/Signal.cpp"
#include "src/sys_module/models/SignalCancel.cpp"
#include "src/sys_module/models/TrailingOrderBase.cpp"
//#include "src/utils/utils.h"
#include "sys_module/StrategyBase.h"
#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;
using namespace sys;

template <typename T>
void log(const T &str) {
    cout << str << endl;
};

class Luffy : public StrategyBase {
  public:
    Luffy() {
        save_to_env(this, "luffy");
        //env->strategies["luffy"] = std::make_shared<Luffy>(*this);
        //throw 1;
    };
    const string get_name() override { return "luffy"; };
    void handle_bar() override {
        //buy(10, "000001", 0, 0, 0, 0, 0, 0, 0, 0.01);
        buy(10, "000001");
        //cout << env->recorder->balance->latest()
        //<< ", "
        //<< env->sys_date
        //<< endl;
    };
};

int main() {
    CsvReader ggss("/Users/chandler/Documents/CLionProjects/OnePyPlus/data/",
                   "000001", "000001");

    Luffy haha;

    vector<string> ticker_list = {"000001"};

    auto go = op::stock(ticker_list,
                        "D",
                        100000,
                        "2017-03-01",
                        "2017-06-01",
                        "tushare");

    go.sunny();
    //cout << (go.env->recorder->balance->latest());
    std::cin.get();
}
