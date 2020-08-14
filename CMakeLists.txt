cmake_minimum_required(VERSION 3.16)
project(ToDoList)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include_directories(src)

add_executable(ToDoList
        src/main.cpp
        src/model/Date.cpp
        src/model/Date.h
        src/model/Task.h
        src/model/FullTask.cpp
        src/model/FullTask.h
        src/api/TaskID.cpp
        src/api/TaskID.h
        src/logic/IDGenerator.cpp
        src/logic/IDGenerator.h
        src/api/TaskService.cpp
        src/api/TaskService.h
        src/api/TaskDTO.cpp
        src/api/TaskDTO.h
        src/api/ReturnType.h
        src/logic/ViewByDate.cpp
        src/logic/ViewByDate.h
        src/logic/ViewByPriority.cpp
        src/logic/ViewByPriority.h
        src/logic/ViewInterface.h
        src/logic/TaskConvertor.cpp
        src/logic/TaskConvertor.h
        src/model/TaskStorage.cpp
        src/model/TaskStorage.h
        src/api/TaskServiceCreator.h
        src/api/TaskPriority.h src/api/ReturnTypeCreator.h)


set(Boost_USE_STATIC_LIBS        ON)  # only find static libs
set(Boost_USE_DEBUG_LIBS         OFF) # ignore debug libs and
set(Boost_USE_RELEASE_LIBS       ON)  # only find release libs
set(Boost_USE_MULTITHREADED      ON)
set(Boost_USE_STATIC_RUNTIME    OFF)

find_package(Boost 1.74.0 REQUIRED COMPONENTS)
if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
endif()

include(GoogleTest)
find_package(GTest REQUIRED)
enable_testing()

add_executable(TestsExecutable
        tests/model/DateTest.cpp
        tests/model/TaskTest.cpp
        tests/api/TaskIDTest.cpp
        src/model/Date.cpp
        src/api/TaskID.cpp
        tests/logic/IDGeneratorTest.cpp
        tests/api/TaskDTOTest.cpp
        tests/logic/ViewByDateTest.cpp
        tests/logic/ViewByPriorityTest.cpp
        tests/logic/TaskConvertorTest.cpp
        tests/model/TaskStorageTest.cpp
        tests/model/FullTaskTest.cpp
        src/logic/IDGenerator.cpp
        src/api/TaskDTO.cpp
        src/logic/ViewByDate.cpp
        src/logic/ViewByPriority.cpp
        src/model/TaskStorage.cpp
        src/model/FullTask.cpp
        src/logic/TaskConvertor.cpp
        )

target_link_libraries(TestsExecutable GTest::GTest GTest::Main)

gtest_discover_tests(TestsExecutable)