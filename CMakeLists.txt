cmake_minimum_required(VERSION 3.15)
project(ToDoList)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(BUILD_SHARED_LIBS OFF)


include_directories(src)
include_directories(tests)

################   Project files  ################
file(GLOB_RECURSE CORE_CPP_SOURCES "src/Core/*.cpp")
file(GLOB_RECURSE CORE_HEADERS  "src/Core/*.h")
file(GLOB_RECURSE CORE_TEST_SOURCES "tests/Core/*.cpp")
file(GLOB_RECURSE CLI_CPP_SOURCES "src/CLI/*.cpp")
file(GLOB_RECURSE CLI_HEADERS "src/CLI/*.cpp")
file(GLOB_RECURSE CLI_TEST_SOURCES "tests/CLI/*.cpp")
file(GLOB_RECURSE MOCK_HEADERS "tests/Mock/*.h")

################   PROTO  ################
add_definitions(-std=gnu++17)
add_definitions(-fPIC)
find_package(Protobuf REQUIRED)
include_directories(${Protobuf_INCLUDE_DIRS})
include_directories(${CMAKE_CURRENT_BINARY_DIR})

file(GLOB_RECURSE PROTO_SOURCES CONFIGURE_DEPENDS ${CMAKE_SOURCE_DIR}/Proto/*.proto )
protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS ${PROTO_SOURCES})
message("Generated ${PROTO_SRCS} ${PROTO_HDRS}")

SET_SOURCE_FILES_PROPERTIES(${PROTO_SRCS} ${PROTO_HDRS} PROPERTIES GENERATED TRUE)

################   BOOST  ################
set(Boost_USE_STATIC_LIBS        ON)  # only find static libs
set(Boost_USE_DEBUG_LIBS         OFF) # ignore debug libs and
set(Boost_USE_RELEASE_LIBS       ON)  # only find release libs
set(Boost_USE_MULTITHREADED      ON)
set(Boost_USE_STATIC_RUNTIME    OFF)

find_package(Boost 1.74.0 REQUIRED COMPONENTS)
if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
endif()

################  GoogleTest   ################
include(GoogleTest)
find_package(GTest REQUIRED)
include_directories(${GMOCK_INCLUDE_DIR})
enable_testing()

set(_PROTOBUF_LIBPROTOBUF protobuf::libprotobuf)
set(_REFLECTION gRPC::grpc++_reflection)


# Find gRPC installation
# Looks for gRPCConfig.cmake file installed by gRPC's cmake installation.
find_package(gRPC REQUIRED)
message(STATUS "Using gRPC ${gRPC_VERSION}")

set(_GRPC_GRPCPP gRPC::grpc++)
find_program(_GRPC_CPP_PLUGIN_EXECUTABLE grpc_cpp_plugin)
get_filename_component(ts_proto "Proto/TaskService.proto" ABSOLUTE)
get_filename_component(ts_proto_path "${ts_proto}" PATH)

set(ts_proto_srcs "${CMAKE_CURRENT_BINARY_DIR}/TaskService.pb.cc")
set(ts_proto_hdrs "${CMAKE_CURRENT_BINARY_DIR}/TaskService.pb.h")
set(ts_grpc_srcs "${CMAKE_CURRENT_BINARY_DIR}/TaskService.grpc.pb.cc")
set(ts_grpc_hdrs "${CMAKE_CURRENT_BINARY_DIR}/TaskService.grpc.pb.h")

add_custom_command(
        OUTPUT "${ts_proto_srcs}" "${ts_proto_hdrs}" "${ts_grpc_srcs}" "${ts_grpc_hdrs}"
        COMMAND protoc
        ARGS -I "${ts_proto_path}"
       --grpc_out "${CMAKE_CURRENT_BINARY_DIR}"
       --cpp_out "${CMAKE_CURRENT_BINARY_DIR}"
       --plugin=protoc-gen-grpc="${_GRPC_CPP_PLUGIN_EXECUTABLE}"
       ${ts_proto}
       DEPENDS ${ts_proto})

include_directories("${CMAKE_CURRENT_BINARY_DIR}")


################  Configuration   ################
add_executable(ToDoList
        ${CORE_HEADERS} ${CORE_CPP_SOURCES}
        ${CLI_CPP_SOURCES} ${CLI_HEADERS}
        src/main.cpp ${PROTO_SRCS} ${PROTO_HDRS}
        ${ts_proto_srcs} ${ts_proto_hdrs}
        ${ts_grpc_srcs} ${ts_grpc_hdrs})

add_executable(TestsExecutableCore
        ${CORE_TEST_SOURCES} ${CORE_CPP_SOURCES} ${MOCK_HEADERS}
        ${PROTO_SRCS} ${PROTO_HDRS}
        ${ts_proto_srcs} ${ts_proto_hdrs}
        ${ts_grpc_srcs} ${ts_grpc_hdrs})

add_executable(TestsExecutableCLI
        ${CLI_TEST_SOURCES} ${CLI_CPP_SOURCES} ${MOCK_HEADERS}
        ${CORE_CPP_SOURCES} ${PROTO_SRCS} ${PROTO_HDRS}
        ${ts_proto_srcs} ${ts_proto_hdrs}
        ${ts_grpc_srcs} ${ts_grpc_hdrs})

target_link_libraries(ToDoList ${Boost_LIBRARIES} ${_REFLECTION}
        ${_GRPC_GRPCPP} ${_PROTOBUF_LIBPROTOBUF})

target_link_libraries(TestsExecutableCore GTest::GTest GTest::Main
        ${GMOCK_LIBRARY} ${GMOCK_MAIN_LIBRARY}
        ${Boost_LIBRARIES} ${_REFLECTION}
        ${_GRPC_GRPCPP} ${_PROTOBUF_LIBPROTOBUF})

target_link_libraries(TestsExecutableCLI GTest::GTest GTest::Main
        ${GMOCK_LIBRARY} ${GMOCK_MAIN_LIBRARY}
        ${Boost_LIBRARIES} ${_REFLECTION}
        ${_GRPC_GRPCPP} ${_PROTOBUF_LIBPROTOBUF})

gtest_discover_tests(TestsExecutableCore)
gtest_discover_tests(TestsExecutableCLI)

add_executable(Server src/server.cpp
        ${CORE_HEADERS} ${CORE_CPP_SOURCES}
        ${PROTO_SRCS} ${PROTO_HDRS}
        ${ts_proto_srcs} ${ts_proto_hdrs}
        ${ts_grpc_srcs} ${ts_grpc_hdrs})

target_link_libraries(Server
        ${Boost_LIBRARIES} ${_REFLECTION}
        ${_GRPC_GRPCPP} ${_PROTOBUF_LIBPROTOBUF})

add_executable(Client src/client.cpp
        ${CLI_HEADERS} ${CLI_CPP_SOURCES}
        ${CORE_HEADERS} ${CORE_CPP_SOURCES}
        ${PROTO_SRCS} ${PROTO_HDRS}
        ${ts_proto_srcs} ${ts_proto_hdrs}
        ${ts_grpc_srcs} ${ts_grpc_hdrs})

target_link_libraries(Client
        ${Boost_LIBRARIES} ${_REFLECTION}
        ${_GRPC_GRPCPP} ${_PROTOBUF_LIBPROTOBUF})


