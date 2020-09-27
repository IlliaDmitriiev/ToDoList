//
// Created by Илля on 19.09.2020.
//

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Core/api/TaskServiceInterface.h"
#include "Core/api/ReturnTypeCreator.h"
#include "CLI/States/Command/AddSubtaskCommand.h"
#include "CLI/Namespaces/CommandMapCreator.h"
#include "CLI/Model/ConsoleContext.h"

using ::testing::Return;

class AddSubtaskTest : public ::testing::Test {
public:
    AddSubtaskCommand state_;
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


TEST_F(AddSubtaskTest, shouldRead1) {
    auto io = std::make_unique<MockConsoleIO>();
    EXPECT_EQ(state_.read(*io), CommandState::Type::Option);
}

TEST_F(AddSubtaskTest, shouldRead2) {
    auto io = std::make_unique<MockConsoleIO>();
    EXPECT_NE(state_.read(*io), CommandState::Type::AddSubtask);
}


TEST_F(AddSubtaskTest, shouldPrint) {
    auto io = std::make_unique<MockConsoleIO>();
    EXPECT_NO_THROW(state_.print(*io));
}


TEST_F(AddSubtaskTest, shouldChange1) {
    auto io = std::make_unique<MockConsoleIO>();
    auto command_map = CommandMap::create();
    auto type = CommandState::Type::AddTask;
    EXPECT_EQ(state_.change(type)->read(*io), command_map[type]->read(*io));
}

TEST_F(AddSubtaskTest, shouldChange2) {
    auto io = std::make_unique<MockConsoleIO>();
    auto command_map = CommandMap::create();
    EXPECT_CALL(*io, input)
            .Times(1)
            .WillOnce(Return("add task"));
    auto type = CommandState::Type::Option;
    EXPECT_EQ(state_.change(type)->read(*io), CommandState::Type::AddTask);
}

TEST_F(AddSubtaskTest, shouldChange3) {
    auto command_map = CommandMap::create();
    auto type = CommandState::Type::Error;
    EXPECT_EQ(state_.change(type), command_map[type]);
}
TEST_F(AddSubtaskTest, shouldExecute) {
    auto io = std::make_unique<MockConsoleIO>();
    auto service = std::make_unique<MockTaskService>();
    auto &ref_to_service = *service;
    auto context = std::make_unique<ConsoleContext>(ConsoleContext::create(std::move(service)));

    EXPECT_CALL(*io, input)
            .Times(5)
            .WillOnce(Return("57"))
            .WillOnce(Return("go to the gym"))
            .WillOnce(Return("sport"))
            .WillOnce(Return("2020-10-10"))
            .WillOnce(Return("2"));
    EXPECT_CALL(*io, output)
            .Times(6)
            .WillRepeatedly(Return());

    EXPECT_NO_THROW(state_.execute(*io, *context));
}
