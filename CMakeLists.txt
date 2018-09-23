CMAKE_MINIMUM_REQUIRED(VERSION 3.9)

project(OnePyPlus)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -std=c++17")

#SET(CMAKE_BUILD_TYPE Release)
SET(CMAKE_BUILD_TYPE Debug)
SET( CMAKE_EXPORT_COMPILE_COMMANDS ON )

SET(EXECUTABLE_OUTPUT_PATH "${PROJECT_SOURCE_DIR}/bin")
SET(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)


INCLUDE_DIRECTORIES( ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/src
    )

SET(source_dir "${PROJECT_SOURCE_DIR}/src")
SET(include_dir "${PROJECT_SOURCE_DIR}/include")

AUX_SOURCE_DIRECTORY("${source_dir}" onepy_src)
AUX_SOURCE_DIRECTORY("${source_dir}/sys_module" onepy_sys)
AUX_SOURCE_DIRECTORY("${source_dir}/sys_module/models" onepy_models)
AUX_SOURCE_DIRECTORY("${source_dir}/sys_module/components" onepy_components)
AUX_SOURCE_DIRECTORY("${source_dir}/builtin_module" onepy_built)
AUX_SOURCE_DIRECTORY("${source_dir}/builtin_module/backtest" onepy_backtest)
AUX_SOURCE_DIRECTORY("${source_dir}/custom_module" onepy_custom)
AUX_SOURCE_DIRECTORY("${source_dir}/utils" onepy_utils)

SET(OnePy_src  
    ${onepy_src}
    ${onepy_sys}
    ${onepy_models}
    ${onepy_components}
    ${onepy_built}
    ${onepy_backtest}
    ${onepy_custom}
    ${onepy_utils})

#链接 MongoDB 静态库
LINK_LIBRARIES(mongocxx)
LINK_LIBRARIES(bsoncxx)
SET(LIB_MONGOCXX_DIR /usr/local/include/bsoncxx/v_noabi)
SET(LIB_BSONCXX_DIR /usr/local/include/mongocxx/v_noabi)

INCLUDE_DIRECTORIES(
    ${LIB_MONGOCXX_DIR}
    ${LIB_BSONCXX_DIR})


LINK_DIRECTORIES("${PROJECT_SOURCE_DIR}/lib")
ADD_LIBRARY(OnePyPluslib SHARED ${OnePy_src})
LINK_LIBRARIES(OnePyPluslib)

# 主程序
add_executable(demo_OnePy ${PROJECT_SOURCE_DIR}/main.cpp
    ${PROJECT_SOURCE_DIR}/Luffy.hpp)
    


# 单元测试
SET(test_dir "${PROJECT_SOURCE_DIR}/tests/")
AUX_SOURCE_DIRECTORY("${test_dir}" test_files)
ADD_EXECUTABLE(test_OnePy ${test_files} )
TARGET_LINK_LIBRARIES(test_OnePy gtest)




#PYTHON_ADD_MODULE(hello hello.cpp)
#FILE(COPY hello.py DESTINATION .)
#ADD_TEST(NAME 01-HelloWorld COMMAND ${PYTHON_EXECUTABLE} hello.py)

FIND_PACKAGE(PythonInterp)

if (PYTHONINTERP_FOUND)
  if (UNIX AND NOT APPLE)
    if (PYTHON_VERSION_MAJOR EQUAL 3)
        FIND_PACKAGE(Boost COMPONENTS python${PYTHON_VERSION_SUFFIX})
        FIND_PACKAGE(PythonInterp 3)
        FIND_PACKAGE(PythonLibs 3 REQUIRED)
    else()
        FIND_PACKAGE(Boost COMPONENTS python)
        FIND_PACKAGE(PythonInterp)
        FIND_PACKAGE(PythonLibs REQUIRED)
    endif()
  else()	
    if (PYTHON_VERSION_MAJOR EQUAL 3)
        FIND_PACKAGE(Boost COMPONENTS python${PYTHON_VERSION_MAJOR}${PYTHON_VERSION_MINOR})
        FIND_PACKAGE(PythonInterp 3)
        FIND_PACKAGE(PythonLibs 3 REQUIRED)
    else()
        FIND_PACKAGE(Boost COMPONENTS python${PYTHON_VERSION_MAJOR}${PYTHON_VERSION_MINOR})
        FIND_PACKAGE(PythonInterp)
        FIND_PACKAGE(PythonLibs REQUIRED)
    endif()
  endif()
else()
    message("Python not found")
endif()


message(STATUS "PYTHON_LIBRARIES = ${PYTHON_LIBRARIES}")
message(STATUS "PYTHON_EXECUTABLE = ${PYTHON_EXECUTABLE}")
message(STATUS "PYTHON_INCLUDE_DIRS = ${PYTHON_INCLUDE_DIRS}")
message(STATUS "Boost_LIBRARIES = ${Boost_LIBRARIES}")

INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS} ${PYTHON_INCLUDE_DIRS})

LINK_LIBRARIES(${Boost_LIBRARIES} ${PYTHON_LIBRARIES}) # Deprecated but so convenient!

FILE(GLOB OnePy_Python_Wrapper "${PROJECT_SOURCE_DIR}/python/*.cpp")
PYTHON_ADD_MODULE(OnePyPlus ${OnePy_Python_Wrapper} )




