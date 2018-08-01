cmake_minimum_required(VERSION 3.9)

project(OnePyPlus)

#set(CMAKE_CXX_STANDARD 17)
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -std=c++17")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

#include_directories(src)
#set(source_dir "${PROJECT_SOURCE_DIR}/src/")
#file(GLOB source_files "${source_dir}/*/*.cpp")
#add_executable(demo ${source_files})

set(test_dir "${PROJECT_SOURCE_DIR}/test/")
file(GLOB test_files "${test_dir}/*.cpp")
add_executable(test_OnePy ${test_files})
target_link_libraries(test_OnePy gtest)
