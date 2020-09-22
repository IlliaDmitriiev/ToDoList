
//
// Created by Илля on 19.09.2020.
//

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Core/api/TaskServiceInterface.h"
#include "Core/api/ReturnTypeCreator.h"
#include "CLI/States/Command/ShowTasksForWeek.h"
#include "CLI/Namespaces/CommandMapCreator.h"
#include "CLI/Model/ConsoleContext.h"

using ::testing::Return;

class ShowTasksForWeekTest : public ::testing::Test {
public:
    ShowTasksForWeek state_;
    void SetUp() override{
    }
};

class MockConsoleIO : public IO {
public:
    MOCK_METHOD(std::string, input, (), (override));
    MOCK_METHOD(void, output, (std::string), (override));
};

class MockTaskService : public TaskServiceInterface {

public:
    MOCK_METHOD(AddTaskResult, addTask, (const TaskDTO&), (override));
    MOCK_METHOD(AddTaskResult, addSubtask, (TaskID, const TaskDTO &), (override));
    MOCK_METHOD(RequstTaskResult, deleteTask, (TaskID), (override));
    MOCK_METHOD(RequstTaskResult, complete, (TaskID), (override));
    MOCK_METHOD(RequstTaskResult, postponeTask, (TaskID, boost::gregorian::date), (override));
    MOCK_METHOD(RequstTaskResult, editTask, (TaskID id, const TaskDTO&), (override));
public:

    MOCK_METHOD(std::vector<TaskDTO>, getSubtasks, (TaskID), (override));
    MOCK_METHOD(std::vector<TaskDTO>, getAllTasksByPriority, (), (override));
    MOCK_METHOD(std::vector<TaskDTO>, getTasksForToday, (), (override));
    MOCK_METHOD(std::vector<TaskDTO>, getTasksForWeek, (), (override));
    MOCK_METHOD(std::optional<TaskDTO>, getTask, (TaskID), (override));

private:
    MOCK_METHOD(bool, removeTask, (const std::weak_ptr<FullTask> &), (override));
};


TEST_F(ShowTasksForWeekTest, shouldRead1) {
    auto io = std::make_unique<MockConsoleIO>();

    EXPECT_EQ(state_.read(*io), CommandState::Type::Submenu);
}

TEST_F(ShowTasksForWeekTest, shouldRead2) {
    auto io = std::make_unique<MockConsoleIO>();

    EXPECT_NE(state_.read(*io), CommandState::Type::DeleteTask);
}


TEST_F(ShowTasksForWeekTest, shouldPrint) {
    auto io = std::make_unique<MockConsoleIO>();

    EXPECT_NO_THROW(state_.print(*io));
}


TEST_F(ShowTasksForWeekTest, shouldChange1) {
    auto io = std::make_unique<MockConsoleIO>();
    auto command_map = CommandMap::create();
    auto type = CommandState::Type::CompleteTask;
    EXPECT_EQ(state_.change(type)->read(*io), CommandState::Type::Option);
}

TEST_F(ShowTasksForWeekTest, shouldChange2) {
    auto io = std::make_unique<MockConsoleIO>();
    auto command_map = CommandMap::create();

    auto type = CommandState::Type::AddTask;
    EXPECT_EQ(state_.change(type)->read(*io), CommandState::Type::Option);
}

TEST_F(ShowTasksForWeekTest, shouldExecute) {
    auto io = std::make_unique<MockConsoleIO>();
    auto service = std::make_unique<MockTaskService>();
    auto &ref_to_service = *service;
    auto context = std::make_unique<ConsoleContext>(ConsoleContext::create(std::move(service)));

    auto task1 = TaskDTO::create(boost::gregorian::date(2020, 10, 10),"name1","label1",TaskPriority::None);
    auto task2 = TaskDTO::create(boost::gregorian::date(2010, 10, 10),"name2","label2",TaskPriority::First);
    auto task3 = TaskDTO::create(boost::gregorian::date(2222, 02, 22),"name3","label3",TaskPriority::First);
    std::vector<TaskDTO> v{task1, task2, task3};

    EXPECT_CALL(ref_to_service, getTasksForWeek)
            .Times(1)
            .WillOnce(Return(v));
    EXPECT_CALL(*io, output)
            .Times(4)
            .WillRepeatedly(Return());

    EXPECT_NO_THROW(state_.execute(*io, *context));
}

