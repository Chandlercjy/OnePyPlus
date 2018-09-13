#include "Environment.h"
#include "EventEngine.h"
#include "OnePy.h"
#include "builtin_module/CsvReader.h"
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
    Luffy() {
        auto module = std::make_shared<Luffy>(*this);
        env->save_module("Luffy", module);
    };
    const string get_name() override { return "luffy"; };
    void handle_bar() override {
        //buy(20, "000001", 0, 0, 0, 0, 0, 0, 0, 0.01);
        buy(20, "000001", 0, 0.01, 0, 0, 0, 0, 0, 0);
        buy(20, "000001", 0, 0.01, 0, 0, 0, 0, 0, 0.01);
        //shortsell(5, "000001",0,0.1,0,0,0,0.01,0,0);
        //std::cout<<  env->feeds["000001"]->execute_price() << "----------------------" << std::endl;
        std::cout<<  env->sys_date << "----------------------" << std::endl;
        std::cout << "balance: "<< env->recorder->balance->latest() <<std::endl; 
        //std::cout << "commission: "<< env->recorder->commission->latest("000001","long") <<std::endl; 
        //std::cout << "position: "<< env->recorder->position->latest("000001","long") <<std::endl; 
        //std::cout << "market_value: "<< env->recorder->market_value->latest("000001","long") <<std::endl; 
    };
};
|| [cd ~/Documents/CLionProjects/OnePyPlus/build && cmake .. && make && ../bin/demo_OnePy]
|| -- Found PythonInterp: /Users/chandler/anaconda/bin/python (found version "3.6.1") 
|| CMake Warning at /usr/local/Cellar/cmake/3.11.1/share/cmake/Modules/FindBoost.cmake:839 (message):
||   New Boost version may have incorrect or missing dependencies and imported
||   targets
|| Call Stack (most recent call first):
||   /usr/local/Cellar/cmake/3.11.1/share/cmake/Modules/FindBoost.cmake:950 (_Boost_COMPONENT_DEPENDENCIES)
||   /usr/local/Cellar/cmake/3.11.1/share/cmake/Modules/FindBoost.cmake:1618 (_Boost_MISSING_DEPENDENCIES)
||   CMakeLists.txt:81 (FIND_PACKAGE)
|| 
|| 
|| -- Boost version: 1.68.0
|| -- Found the following Boost libraries:
|| --   python36
|| -- Found PythonInterp: /Users/chandler/anaconda/bin/python (found suitable version "3.6.1", minimum required is "3") 
|| -- PYTHON_LIBRARIES = /Users/chandler/anaconda/lib/libpython3.6m.dylib
|| -- PYTHON_EXECUTABLE = /Users/chandler/anaconda/bin/python
|| -- PYTHON_INCLUDE_DIRS = /Users/chandler/anaconda/include/python3.6m
|| -- Boost_LIBRARIES = /usr/local/lib/libboost_python36.dylib
|| -- Configuring done
|| -- Generating done
|| -- Build files have been written to: /Users/chandler/Documents/CLionProjects/OnePyPlus/build
|| [ 31%] Built target OnePyPlus
|| [ 69%] Built target test_OnePy
|| [100%] Built target demo_OnePy
||  正在初始化OnePy
|| OnePy初始化成功!!
|| 开始寻找OnePiece之旅~~~
|| 2018-02-05 00:00:00----------------------
|| balance: 100000
|| 2018-02-06 00:00:00----------------------
|| balance: 99999.6
|| 2018-02-07 00:00:00----------------------
|| balance: 99998.9
|| 2018-02-08 00:00:00----------------------
|| balance: 99917.9
|| 2018-02-09 00:00:00----------------------
|| balance: 99858.5
|| 2018-02-12 00:00:00----------------------
|| balance: 99828.6
|| 2018-02-13 00:00:00----------------------
|| balance: 99840.1
|| 2018-02-14 00:00:00----------------------
|| balance: 99862.6
|| 2018-02-15 00:00:00----------------------
|| balance: 99856.7
|| 2018-02-16 00:00:00----------------------
|| balance: 99856.7
|| 2018-02-19 00:00:00----------------------
|| balance: 99856.7
|| 2018-02-20 00:00:00----------------------
|| balance: 99856.7
|| 2018-02-21 00:00:00----------------------
|| balance: 99856.7
|| 2018-02-22 00:00:00----------------------
|| balance: 99890.9
|| 2018-02-23 00:00:00----------------------
|| balance: 99981.6
|| 2018-02-26 00:00:00----------------------
|| balance: 99956.4
|| 2018-02-27 00:00:00----------------------
|| balance: 99940.9
|| 2018-02-28 00:00:00----------------------
|| balance: 99866.1
|| 2018-03-01 00:00:00----------------------
|| balance: 99837.4
|| 2018-03-02 00:00:00----------------------
|| balance: 99840.9
|| 2018-03-05 00:00:00----------------------
|| balance: 99843.9
|| 2018-03-06 00:00:00----------------------
|| balance: 99846.3
|| 2018-03-07 00:00:00----------------------
|| balance: 99887.4
|| 2018-03-08 00:00:00----------------------
|| balance: 99869.4
|| 2018-03-09 00:00:00----------------------
|| balance: 99890.8
|| 2018-03-12 00:00:00----------------------
|| balance: 99891.7
|| 2018-03-13 00:00:00----------------------
|| balance: 99863.2
|| 2018-03-14 00:00:00----------------------
|| balance: 99842.4
|| 2018-03-15 00:00:00----------------------
|| balance: 99782.2
|| 2018-03-16 00:00:00----------------------
|| balance: 99758.4
|| 2018-03-19 00:00:00----------------------
|| balance: 99737.1
|| 2018-03-20 00:00:00----------------------
|| balance: 99770.3
|| 2018-03-21 00:00:00----------------------
|| balance: 99848
|| 2018-03-22 00:00:00----------------------
|| balance: 99830.4
|| 2018-03-23 00:00:00----------------------
|| balance: 99586.8
|| 2018-03-26 00:00:00----------------------
|| balance: 99547.3
|| 2018-03-27 00:00:00----------------------
|| balance: 99526.3
|| 2018-03-28 00:00:00----------------------
|| balance: 99415.9
|| 2018-03-29 00:00:00----------------------
|| balance: 99445.9
|| 2018-03-30 00:00:00----------------------
|| balance: 99511.6
|| Backtest Completed!
|| 99445.1
|| [Finished in 1 seconds]

