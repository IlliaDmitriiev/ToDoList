cmake_minimum_required(VERSION 3.16)
project(ToDoList)

set(CMAKE_CXX_STANDARD 17)

add_executable(ToDoList
        src/main.cpp
        src/model/Date.cpp
        src/model/Date.h
        src/model/Task.h
        src/logic/StorageByPrior.cpp
        src/logic/StorageByPrior.h
        src/logic/FullTask.cpp
        src/logic/FullTask.h
        src/model/TaskID.cpp
        src/model/TaskID.h
        src/logic/IDGenerator.cpp
        src/logic/IDGenerator.h
        src/logic/StorageByDate.cpp
        src/logic/StorageByDate.h
        src/api/TaskService.cpp
        src/api/TaskService.h
        src/logic/TaskDTO.cpp
        src/logic/TaskDTO.h
        src/logic/ViewByDate.cpp
        src/logic/ViewByDate.h
        src/logic/ViewByPriority.cpp
        src/logic/ViewByPriority.h
        src/logic/View.cpp
        src/logic/View.h
        src/logic/Convertor.cpp
        src/logic/Convertor.h
        src/logic/StorageForSharedPtr.cpp
        src/logic/StorageForSharedPtr.h
        src/logic/Cleaner.cpp
        src/logic/Cleaner.h
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
        src/model/TaskID.cpp
        tests/logic/IDGeneratorTest.cpp
        tests/logic/TaskDTOTest.cpp
        tests/logic/ViewByDateTest.cpp
        tests/logic/ViewByPriorityTest.cpp
        tests/logic/StorageByPriorTest.cpp
        tests/logic/ConvertorTest.cpp
        tests/logic/StorageByDateTest.cpp
        tests/logic/StorageForSharedPtrTest.cpp
        src/logic/IDGenerator.cpp
        src/logic/TaskDTO.cpp
        src/logic/ViewByDate.cpp
        src/logic/ViewByPriority.cpp
        src/logic/StorageForSharedPtr.cpp
        src/logic/StorageByDate.cpp
        src/logic/StorageByPrior.cpp
        src/logic/FullTask.cpp
        src/logic/View.cpp
        src/logic/Convertor.cpp
        src/logic/Cleaner.cpp
        )

target_link_libraries(TestsExecutable GTest::GTest GTest::Main)

gtest_discover_tests(TestsExecutable)