cmake_minimum_required(VERSION 3.16)
project(ToDoList)

set(CMAKE_CXX_STANDARD 17)

add_executable(TestP
        src/main.cpp
        src/model/Date.h
        src/model/Task.h
        src/logic/StorageByPrior.h
        src/logic/FullTask.h
        src/logic/DateLogic.h
        src/model/TaskID.h
        src/logic/IDGenerator.h
        src/logic/StorageByDate.h
        src/api/TaskService.h
        src/logic/TaskDTO.h
        )

include_directories(src)
include_directories(src/api)
include_directories(src/logic)
include_directories(src/model)

include_directories(tests)

include(GoogleTest)
find_package(GTest REQUIRED)
enable_testing()

add_executable(TestsExecutable
        tests/model/DateTest.cpp
        tests/model/TaskTest.cpp
        tests/model/TaskIDTest.cpp
        src/model/Date.cpp
        src/model/TaskID.cpp)

target_link_libraries(TestsExecutable GTest::GTest GTest::Main)

gtest_discover_tests(TestsExecutable)