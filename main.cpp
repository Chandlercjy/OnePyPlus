#include "src/Constants.h"
#include "src/Environment.cpp"
#include "src/EventEngine.cpp"
#include "src/OnePy.cpp"
#include "src/OnePy.h"
#include "src/builtin_module/CsvReader.cpp"
#include "src/builtin_module/StockRecorder.cpp"
#include "src/config.cpp"
#include "src/sys_module//components/MarketMaker.cpp"
#include "src/sys_module/BrokerBase.cpp"
#include "src/sys_module/CleanerBase.cpp"
#include "src/sys_module/ReaderBase.cpp"
#include "src/sys_module/RecorderBase.cpp"
#include "src/sys_module/RiskManagerBase.cpp"
#include "src/sys_module/StrategyBase.cpp"
#include "src/sys_module/models/BarBase.cpp"
#include "src/sys_module/models/Calendar.cpp"
#include "src/sys_module/models/Signal.cpp"
#include "src/sys_module/models/SignalCancel.cpp"
#include "src/utils/utils.h"
#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;
using namespace except;

template <typename T>
void log(T &str) {
    cout << str << endl;
};

void log2(string &str) {
    cout << str << endl;
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
    op::StockRecorder a;
    go.sunny();
    //vector<int> test{1, 2, 3, 4, 5};
    //assert(utils::is_element_in_vector(test, 3) == true);

    std::cin.get();
}
