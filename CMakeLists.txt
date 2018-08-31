cmake_minimum_required(VERSION 3.9)

project(OnePyPlus)

#set(CMAKE_CXX_STANDARD 17)
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -std=c++17")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

set( CMAKE_EXPORT_COMPILE_COMMANDS ON )
SET(CMAKE_BUILD_TYPE Release)
#SET(CMAKE_BUILD_TYPE Debug)

set(EXECUTABLE_OUTPUT_PATH "${PROJECT_SOURCE_DIR}/bin")
#set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)


include_directories("${PROJECT_SOURCE_DIR}/include")
set(source_dir "${PROJECT_SOURCE_DIR}/src")

AUX_SOURCE_DIRECTORY(${source_dir} onepy_src)
AUX_SOURCE_DIRECTORY(${source_dir}/sys_module onepy_sys)
AUX_SOURCE_DIRECTORY(${source_dir}/sys_module/models onepy_models)
AUX_SOURCE_DIRECTORY(${source_dir}/sys_module/components onepy_components)
AUX_SOURCE_DIRECTORY(${source_dir}/builtin_module onepy_built)
AUX_SOURCE_DIRECTORY(${source_dir}/builtin_module/backtest_stock onepy_stock)
AUX_SOURCE_DIRECTORY(${source_dir}/custom_module onepy_custom)
AUX_SOURCE_DIRECTORY(${source_dir}/utils onepy_utils)

ADD_EXECUTABLE(demo 
    ${onepy_src}
    ${onepy_sys}
    ${onepy_models}
    ${onepy_components}
    ${onepy_built}
    ${onepy_stock}
    ${onepy_custom}
    ${onepy_utils}
    )


SET_TARGET_PROPERTIES(demo PROPERTIES LINKER_LANGUAGE CXX)


#file(GLOB source_files 
    #"${source_dir}/uitls/*.cpp"
    #"${source_dir}/sys_module/*.cpp"
    #"${source_dir}/sys_module/models/*.cpp"
    #"${source_dir}/sys_module/components/*.cpp"
    #"${source_dir}/builtin_module/*.cpp"
    #"${source_dir}/builtin_module/backtest_stock/*.cpp"
    #"${source_dir}/custom_module/*.cpp"
    #"${PROJECT_SOURCE_DIR}/main.cpp" )
#add_executable(demo ${source_files})


#set(test_dir "${PROJECT_SOURCE_DIR}/test/")
#file(GLOB test_files "${test_dir}/*.cpp")
#add_executable(test_OnePy ${test_files})
#target_link_libraries(test_OnePy gtest)
