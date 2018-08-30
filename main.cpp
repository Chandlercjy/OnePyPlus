#include "src/Environment.cpp"
#include "src/EventEngine.cpp"
#include "src/OnePy.cpp"
#include "src/builtin_module/CsvReader.cpp"
#include "src/builtin_module/backtest_stock/StockBroker.cpp"
#include "src/builtin_module/backtest_stock/StockRecorder.cpp"
#include "src/builtin_module/backtest_stock/StockSeries.cpp"
#include "src/config.cpp"
#include "src/sys_module/BrokerBase.cpp"
#include "src/sys_module/CleanerBase.cpp"
#include "src/sys_module/ReaderBase.cpp"
#include "src/sys_module/RecorderBase.cpp"
#include "src/sys_module/RiskManagerBase.cpp"
#include "src/sys_module/StrategyBase.cpp"
#include "src/sys_module/components/MarketMaker.cpp"
#include "src/sys_module/components/OrderChencker.cpp"
#include "src/sys_module/components/OrderGenerator.cpp"
#include "src/sys_module/components/SignalGenerator.cpp"
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
#include "src/utils/utils.h"
#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;
using namespace except;

template <typename T>
void log(const T &str) {
    cout << str << endl;
};

class Luffy : public op::StrategyBase {
  public:
    Luffy() {
        save_to_env(this, "luffy");
        //env->strategies["luffy"] = std::make_shared<Luffy>(*this);
        //throw 1;
    };
    const string get_name() override { return "Luffy"; };
    void handle_bar() override {
        //buy(10, "000001", 0, 0, 0, 0, 0, 0, 0, 0.01);
        buy(10, "000001");
    };
};

int main() {
    sys::CsvReader ggss("./data/",
                        "000001", "000001");
    op::OnePiece go;
    //go.env->readers["ggg"] = &ggss;
    //auto ll = sys::BarBase("ggg", "D");
    //ll.initialize(8);
    //log(ll.date());
    //log(ll.previous_ohlc->date);

    //go.env->event_engine->put(sys::EVENT::Data_cleaned);
    Luffy gggks;
    log(gggks.env->instrument);

    //op::Environment *env = op::Environment::get_instance();
    //env->strategies["kjkjjkj"] = std::make_shared<Luffy>();
    //throw 1;
    sys::StockBroker b;
    op::StockRecorder a;
    go.sunny();
    //vector<int> test{1, 2, 3, 4, 5};
    //assert(utils::is_element_in_vector(test, 3) == true);

    std::cin.get();
}
