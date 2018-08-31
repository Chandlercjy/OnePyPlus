CMAKE_MINIMUM_REQUIRED(VERSION 3.9)

project(OnePyPlus)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -std=c++17")
#SET(CMAKE_BUILD_TYPE Release)
SET(CMAKE_BUILD_TYPE Debug)

SET(EXECUTABLE_OUTPUT_PATH "${PROJECT_SOURCE_DIR}/bin")
SET(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)


INCLUDE_DIRECTORIES(
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/src
    )

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



#LINK_DIRECTORIES("${PROJECT_SOURCE_DIR}/lib")
#LINK_LIBRARIES(demo_lib)



add_executable(demo_OnePy ${PROJECT_SOURCE_DIR}/main.cpp)

#SET(total_files ${source_dir}/All.cpp)
#ADD_LIBRARY(demo_lib SHARED ${total_files})
#INSTALL(TARGETS demo_lib LIBRARY DESTINATION lib)

SET(test_dir "${PROJECT_SOURCE_DIR}/test/")
AUX_SOURCE_DIRECTORY("${test_dir}" test_files)
ADD_EXECUTABLE(test_OnePy 
    ${test_files} 
    ${source_dir}/All.cpp
    )
TARGET_LINK_LIBRARIES(test_OnePy gtest)

