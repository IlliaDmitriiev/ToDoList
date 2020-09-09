cmake_minimum_required(VERSION 3.16)
project(ToDoList)

set(CMAKE_CXX_STANDARD 17)

include_directories(src)

file(GLOB CORE_CPP_SOURCES
        "src/Core/api/*.cpp"
        "src/Core/logic/*.cpp"
        "src/Core/model/*.cpp"
        )

file(GLOB CORE_HEADERS
        "src/Core/api/*.h"
        "src/Core/logic/*.h"
        "src/Core/model/*.h"
        )

file(GLOB CORE_TEST_SOURCES
        "tests/Core/api/*.cpp"
        "tests/Core/logic/*.cpp"
        "tests/Core/model/*.cpp"
        )

add_executable(ToDoList ${CORE_HEADERS} ${CORE_CPP_SOURCES}  src/main.cpp)

set(Boost_USE_STATIC_LIBS        ON)  # only find static libs
set(Boost_USE_DEBUG_LIBS         OFF) # ignore debug libs and
set(Boost_USE_RELEASE_LIBS       ON)  # only find release libs
set(Boost_USE_MULTITHREADED      ON)
set(Boost_USE_STATIC_RUNTIME    OFF)

find_package(Boost 1.74.0 REQUIRED COMPONENTS)
if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
endif()

target_link_libraries(ToDoList -static)
target_link_libraries(ToDoList ${Boost_LIBRARIES})

include(GoogleTest)
find_package(GTest REQUIRED)
include_directories(${GMOCK_INCLUDE_DIR})
enable_testing()


add_executable(TestsExecutable ${CORE_TEST_SOURCES} ${CORE_CPP_SOURCES} )

target_link_libraries(TestsExecutable GTest::GTest GTest::Main ${GMOCK_LIBRARY} ${GMOCK_MAIN_LIBRARY})

gtest_discover_tests(TestsExecutable)