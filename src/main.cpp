#include "OnePy.cpp"
#include "config.h"
#include "sys_module/components/Exceptions.h"
#include "sys_module/models/BarBase.cpp"

#include <experimental/vector>
#include <iostream>
#include <queue>
#include <string>

using namespace std;
using namespace except;

template <typename T>
void log(T &str) {
    cout << str << endl;
};

void log2(string str) {
    cout << str << endl;
};

struct luffy {
    luffy(string date, double open, double high,
          double low, double close, double volume)
        : date(date),
          open(open),
          high(high),
          low(low),
          close(close),
          volume(volume){};

    string date;
    double open;
    double high;
    double low;
    double close;
    double volume;
};

int main() {

    CsvReader ggss("./test.csv", "ggg");
    auto gg = ggss.bar_series;
    //cout << gg->date;
    BarBase kk(gg);
    //kk.next();
    //kk.next();

    //dd.pop();
    //int *s = nullptr;
    //cout << *s << endl;
    string hhh = "ggg";
    OhlcStruct haha(hhh, 1, 1, 11, 1, 1);
    //log(haha.open);
    OnePiece go;

    //go.env->event_bus.put(EVENT::Data_cleaned);
    //go.env->event_bus.put(EVENT::None);
    //auto ll = go.env->event_bus.get();
    //go.env->event_bus.put(EVENT::Data_cleaned);
    //ll = go.env->event_bus.get();
    //go.env->event_bus.put(EVENT::Data_cleaned);
    //go.sunny();
    //if (EVENT::Market_updated != EVENT::Data_cleaned)
    //log("sss");

    try {
        throw BlowUpError{};
    } catch (BlowUpError &e) {
        cout << e.what() << endl;
    };

    //switch (4) {
    //case 1:
    //log("kkkk");
    //break;
    //case 2:
    //log("ggggg");
    //break;
    //default:
    //log("default");
    //}

    /*    for (auto i : config::EVENT_LOOP) {*/
    //print_type(i.if_event);
    /*    }*/
    //config::SingleLoop *aa;
    //config::EVENT_LOOP.push_back(aa);
    std::cin.get();
}
