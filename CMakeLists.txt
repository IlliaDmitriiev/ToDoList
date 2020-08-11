cmake_minimum_required(VERSION 3.16)
project(ToDoList)

set(CMAKE_CXX_STANDARD 17)

add_executable(ToDoList
        src/main.cpp
        src/model/Date.cpp
        src/model/Date.h
        src/model/Task.h
        src/logic/FullTask.cpp
        src/logic/FullTask.h
        src/api/TaskID.cpp
        src/api/TaskID.h
        src/logic/IDGenerator.cpp
        src/logic/IDGenerator.h
        src/api/TaskService.cpp
        src/api/TaskService.h
        src/api/TaskDTO.cpp
        src/api/TaskDTO.h
        src/api/TaskCreationResult.cpp
        src/api/TaskCreationResult.h
        src/logic/ViewByDate.cpp
        src/logic/ViewByDate.h
        src/logic/ViewByPriority.cpp
        src/logic/ViewByPriority.h
        src/logic/View.cpp
        src/logic/View.h
        src/logic/TaskConvertor.cpp
        src/logic/TaskConvertor.h
        src/logic/StorageForSharedPtr.cpp
        src/logic/StorageForSharedPtr.h
        )

include_directories(src)


include(GoogleTest)
find_package(GTest REQUIRED)
enable_testing()

add_executable(TestsExecutable
        tests/model/DateTest.cpp
        tests/model/TaskTest.cpp
        tests/model/TaskIDTest.cpp
        src/model/Date.cpp
        src/api/TaskID.cpp
        tests/logic/IDGeneratorTest.cpp
        tests/api/TaskDTOTest.cpp
        tests/logic/ViewByDateTest.cpp
        tests/logic/ViewByPriorityTest.cpp
        tests/logic/TaskConvertorTest.cpp
        tests/logic/StorageForSharedPtrTest.cpp
        tests/logic/ViewTest.cpp
        tests/logic/FullTaskTest.cpp
        tests/api/TaskCreationResultTest.cpp
        src/logic/IDGenerator.cpp
        src/api/TaskDTO.cpp
        src/api/TaskCreationResult.cpp
        src/logic/ViewByDate.cpp
        src/logic/ViewByPriority.cpp
        src/logic/StorageForSharedPtr.cpp
        src/logic/FullTask.cpp
        src/logic/View.cpp
        src/logic/TaskConvertor.cpp
        )

target_link_libraries(TestsExecutable GTest::GTest GTest::Main)

gtest_discover_tests(TestsExecutable)