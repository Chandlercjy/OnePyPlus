//#include "src/All.cpp"
#include "Luffy.hpp"

#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;
using namespace op;

int main() {
    //CsvReader ggss("/Users/chandler/Documents/CLionProjects/OnePyPlus/data/",
                   //"000001", "000001");
    MongodbReader lalala("000001_tushare","000001");


    Luffy haha("keke");

    vector<string> ticker_list = {"000001"};

    auto go = op::stock(ticker_list,
                        "H1",
                        100000,
                        "2018-02-05",
                        "2018-02-08",
                        "tushare");

    go.env->is_show_today_signals=true;
    go.sunny();
    cout << (go.env->recorder->balance->latest());
    //cout << "hahah";
    std::cin.get();
}
