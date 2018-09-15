#include "Environment.h"
#include "EventEngine.h"
#include "OnePy.h"
#include "builtin_module/CsvReader.h"
#include "builtin_module/MongodbReader.h"
#include "builtin_module/backtest_stock/StockBroker.h"
#include "builtin_module/backtest_stock/StockRecorder.h"
#include "builtin_module/backtest_stock/StockSeries.h"
#include "config.h"
#include "custom_module/backtest.h"
#include "sys_module/BrokerBase.h"
#include "sys_module/CleanerBase.h"
#include "sys_module/ReaderBase.h"
#include "sys_module/RecorderBase.h"
#include "sys_module/RiskManagerBase.h"
#include "sys_module/StrategyBase.h"
#include "sys_module/components/MarketMaker.h"
#include "sys_module/components/OrderGenerator.h"
#include "sys_module/components/PendingOrderChecker.h"
#include "sys_module/components/SignalGenerator.h"
#include "sys_module/components/SubmitOrderChecker.h"
#include "sys_module/components/TriggeredSignalGenerator.h"
#include "sys_module/models/BarBase.h"
#include "sys_module/models/Calendar.h"
#include "sys_module/models/CancelOrderBase.h"
#include "sys_module/models/Counter.h"
#include "sys_module/models/GeneralOrder.h"
#include "sys_module/models/OrderBase.h"
#include "sys_module/models/PendingOrder.h"
#include "sys_module/models/SeriesBase.h"
#include "sys_module/models/Signal.h"
#include "sys_module/models/SignalCancel.h"
#include "sys_module/models/TrailingOrderBase.h"

#pragma once

class Luffy : public op::StrategyBase {
  public:
    Luffy(const string &name)
        : StrategyBase(name) {
        auto module = std::make_shared<Luffy>(*this);
        env->save_module("Luffy", module);
    };
    void handle_bar() override {
//        shortsell(20, "000001", 0, 0.01, 0, 0, 0, 0, 0, 0.01);
       buy(20, "000001", 3, 0, 3, 0, 0, 0, 0, 0);


        //shortsell(5, "000001",0,0.1,0,0,0,0.01,0,0);
//        std::cout<<  env->feeds["000001"]->execute_price() << "----------------------" << std::endl;
        //std::cout << env->sys_date << "----------------------" << std::endl;
//        std::cout << "balance: " << env->recorder->balance->latest() << std::endl;
        //std::cout << "commission: "<< env->recorder->commission->latest("000001","long") <<std::endl;
        //std::cout << "position: "<< env->recorder->position->latest("000001","long") <<std::endl;
        //std::cout << "market_value: "<< env->recorder->market_value->latest("000001","long") <<std::endl;
    };
};
