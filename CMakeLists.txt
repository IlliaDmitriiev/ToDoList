cmake_minimum_required(VERSION 3.15)
project(ToDoList)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(BUILD_SHARED_LIBS OFF)


include_directories(src)
include_directories(tests)

file(GLOB_RECURSE CORE_CPP_SOURCES "src/Core/*.cpp")
file(GLOB_RECURSE CORE_HEADERS  "src/Core/*.h")
file(GLOB_RECURSE CORE_TEST_SOURCES "tests/Core/*.cpp")
file(GLOB_RECURSE CLI_CPP_SOURCES "src/CLI/*.cpp")
file(GLOB_RECURSE CLI_HEADERS "src/CLI/*.cpp")
file(GLOB_RECURSE CLI_TEST_SOURCES "tests/CLI/*.cpp")
file(GLOB_RECURSE MOCK_HEADERS "tests/Mock/*.h")

add_definitions(-std=gnu++17)
add_definitions(-fPIC)
find_package(Protobuf REQUIRED)
include_directories(${Protobuf_INCLUDE_DIRS})
include_directories(${CMAKE_CURRENT_BINARY_DIR})

file(GLOB_RECURSE PROTO_SOURCES CONFIGURE_DEPENDS ${CMAKE_SOURCE_DIR}/Proto/*.proto )
protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS ${PROTO_SOURCES})
message("Generated ${PROTO_SRCS} ${PROTO_HDRS}")

SET_SOURCE_FILES_PROPERTIES(${PROTO_SRCS} ${PROTO_HDRS} PROPERTIES GENERATED TRUE)

add_executable(ToDoList
        ${CORE_HEADERS} ${CORE_CPP_SOURCES}
        ${CLI_CPP_SOURCES} ${CLI_HEADERS}
        src/main.cpp ${PROTO_SRCS} ${PROTO_HDRS})

set(Boost_USE_STATIC_LIBS        ON)  # only find static libs
set(Boost_USE_DEBUG_LIBS         OFF) # ignore debug libs and
set(Boost_USE_RELEASE_LIBS       ON)  # only find release libs
set(Boost_USE_MULTITHREADED      ON)
set(Boost_USE_STATIC_RUNTIME    OFF)

find_package(Boost 1.74.0 REQUIRED COMPONENTS)
if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
endif()

target_link_libraries(ToDoList ${Boost_LIBRARIES})

include(GoogleTest)
find_package(GTest REQUIRED)
include_directories(${GMOCK_INCLUDE_DIR})
enable_testing()

add_executable(TestsExecutableCore
        ${CORE_TEST_SOURCES} ${CORE_CPP_SOURCES} ${MOCK_HEADERS}
        ${PROTO_SRCS} ${PROTO_HDRS})
add_executable(TestsExecutableCLI
        ${CLI_TEST_SOURCES} ${CLI_CPP_SOURCES} ${MOCK_HEADERS}
        ${CORE_CPP_SOURCES} ${PROTO_SRCS} ${PROTO_HDRS} )

target_link_libraries(TestsExecutableCore GTest::GTest GTest::Main
        ${GMOCK_LIBRARY} ${GMOCK_MAIN_LIBRARY} ${Protobuf_LIBRARIES})
target_link_libraries(TestsExecutableCLI GTest::GTest GTest::Main
        ${GMOCK_LIBRARY} ${GMOCK_MAIN_LIBRARY} ${Protobuf_LIBRARIES})

gtest_discover_tests(TestsExecutableCore)
gtest_discover_tests(TestsExecutableCLI)

target_link_libraries(ToDoList ${Protobuf_LIBRARIES})
