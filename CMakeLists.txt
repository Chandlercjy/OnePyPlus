CMAKE_MINIMUM_REQUIRED(VERSION 3.9)

project(OnePyPlus)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -std=c++17")
#SET(CMAKE_BUILD_TYPE Release)
#SET(CMAKE_BUILD_TYPE Debug)

SET(EXECUTABLE_OUTPUT_PATH "${PROJECT_SOURCE_DIR}/bin")
##SET(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)


INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/include)

SET(source_dir "${PROJECT_SOURCE_DIR}/src")
SET(include_dir "${PROJECT_SOURCE_DIR}/include")

AUX_SOURCE_DIRECTORY("${source_dir}" onepy_src)
AUX_SOURCE_DIRECTORY("${source_dir}/sys_module" onepy_sys)
AUX_SOURCE_DIRECTORY("${source_dir}/sys_module/models" onepy_models)
AUX_SOURCE_DIRECTORY("${source_dir}/sys_module/components" onepy_components)
AUX_SOURCE_DIRECTORY("${source_dir}/builtin_module" onepy_built)
AUX_SOURCE_DIRECTORY("${source_dir}/builtin_module/backtest_stock" onepy_stock)
AUX_SOURCE_DIRECTORY("${source_dir}/custom_module" onepy_custom)
AUX_SOURCE_DIRECTORY("${source_dir}/utils" onepy_utils)


SET(total_files
    ${PROJECT_SOURCE_DIR}/main.cpp
    ${onepy_src}
    ${onepy_sys}
    ${onepy_models}
    ${onepy_components}
    ${onepy_built}
    ${onepy_stock}
    ${onepy_custom}
    ${onepy_utils}

    ${include_dir}/Environment.h
    ${include_dir}/EventEngine.h
    ${include_dir}/OnePy.h
    ${include_dir}/builtin_module/CsvReader.h
    ${include_dir}/builtin_module/backtest_stock/StockBroker.h
    ${include_dir}/builtin_module/backtest_stock/StockRecorder.h
    ${include_dir}/builtin_module/backtest_stock/StockSeries.h
    ${include_dir}/config.h
    ${include_dir}/Constants.h
    ${include_dir}/DataType.h
    ${include_dir}/Exceptions.h
    ${include_dir}/utils/arrow.h
    ${include_dir}/utils/date.h
    ${include_dir}/utils/easy_func.h
    ${include_dir}/utils/utils.h
    ${include_dir}/custom_module/backtest.h
    ${include_dir}/sys_module/BrokerBase.h
    ${include_dir}/sys_module/CleanerBase.h
    ${include_dir}/sys_module/ReaderBase.h
    ${include_dir}/sys_module/RecorderBase.h
    ${include_dir}/sys_module/RiskManagerBase.h
    ${include_dir}/sys_module/StrategyBase.h
    ${include_dir}/sys_module/components/MarketMaker.h
    ${include_dir}/sys_module/components/OrderGenerator.h
    ${include_dir}/sys_module/components/PendingOrderChecker.h
    ${include_dir}/sys_module/components/SignalGenerator.h
    ${include_dir}/sys_module/components/SubmitOrderChecker.h
    ${include_dir}/sys_module/components/TriggeredSignalGenerator.h
    ${include_dir}/sys_module/models/BarBase.h
    ${include_dir}/sys_module/models/Calendar.h
    ${include_dir}/sys_module/models/CancelOrderBase.h
    ${include_dir}/sys_module/models/GeneralOrder.h
    ${include_dir}/sys_module/models/OrderBase.h
    ${include_dir}/sys_module/models/PendingOrderBase.h
    ${include_dir}/sys_module/models/SeriesBase.h
    ${include_dir}/sys_module/models/Signal.h
    ${include_dir}/sys_module/models/SignalCancel.h
    ${include_dir}/sys_module/models/TrailingOrderBase.h
 )

add_executable(demo ${total_files})

#ADD_LIBRARY(demo_lib SHARED ${total_files})
#INSTALL(TARGETS demo_lib LIBRARY DESTINATION lib)

#SET(test_dir "${PROJECT_SOURCE_DIR}/test/")
#AUX_SOURCE_DIRECTORY("${test_dir}" test_files)
#ADD_EXECUTABLE(test_OnePy 
#${test_files} 
#${source_dir}/All.cpp
#)
#TARGET_LINK_LIBRARIES(test_OnePy gtest)

#cmake_minimum_required(VERSION 2.6)
#project(OnePyPlus)
#add_definitions(-std=c++17)
##set(test_source main.cpp)
#
#SET(EXECUTABLE_OUTPUT_PATH "${PROJECT_SOURCE_DIR}/bin")
###SET(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)
#
#
#INCLUDE_DIRECTORIES("${PROJECT_SOURCE_DIR}/include")
#SET(source_dir "${PROJECT_SOURCE_DIR}/src")
#
#AUX_SOURCE_DIRECTORY("${source_dir}" onepy_src)
#AUX_SOURCE_DIRECTORY("${source_dir}/sys_module" onepy_sys)
#AUX_SOURCE_DIRECTORY("${source_dir}/sys_module/models" onepy_models)
#AUX_SOURCE_DIRECTORY("${source_dir}/sys_module/components" onepy_components)
#AUX_SOURCE_DIRECTORY("${source_dir}/builtin_module" onepy_built)
#AUX_SOURCE_DIRECTORY("${source_dir}/builtin_module/backtest_stock" onepy_stock)
#AUX_SOURCE_DIRECTORY("${source_dir}/custom_module" onepy_custom)
#AUX_SOURCE_DIRECTORY("${source_dir}/utils" onepy_utils)
#
#add_executable(demo
#    ${PROJECT_SOURCE_DIR}/main.cpp
#    ${onepy_src}
#    ${onepy_sys}
#    ${onepy_models}
#    ${onepy_components}
#    ${onepy_built}
#    ${onepy_stock}
#    ${onepy_custom}
#    ${onepy_utils}
#)   #这行第一个才是文件名
#INSTALL(TARGETS demo DESTINATION "testbin")
