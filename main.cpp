//#include "src/All.cpp"
#include "Luffy.hpp"

#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;
using namespace op;

class SMA : public CleanerBase {
  public:
    SMA(const int rolling_window,
        int buffer_day,
        const string &frequency)
        : CleanerBase("SMA",
                      rolling_window,
                      buffer_day,
                      frequency) {
        auto module = std::make_shared<SMA>(*this);
        env->save_module(name, module);
    };
    double calculate(const string &ticker) override{
        cout << "keke" << endl;
        return 0;
    };
    ~SMA(){
            CleanerBase::~CleanerBase();

    };
};

int main() {
    //CsvReader ggss("/Users/chandler/Documents/CLionProjects/OnePyPlus/data/",
    //"000001", "000001");
    //MongodbReader lalala("000001_tushare", "000001");
    MongodbReader lalala("EUR_USD_oanda", "EUR_USD");

    Luffy haha("keke");
    SMA jhjh(10, 10, "D");

    vector<string> ticker_list = {"000001"};

    //auto go = op::stock(ticker_list,
                        //"D",
                        //100000,
                        //"2018-01-25",
                        //"2018-04-01",
                        //"tushare");

    auto go = op::forex(ticker_list,
                        "M30",
                        100000,
                        "2017-01-25",
                        "2017-03-01",
                        "oanda");

    //go.env->is_show_today_signals=true;
    go.sunny();
    cout << (go.env->recorder->balance->latest());
    //cout << "hahah";
//    std::cin.get();
}
