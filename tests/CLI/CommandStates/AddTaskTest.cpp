//
// Created by Илля on 19.09.2020.
//

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Core/api/TaskServiceInterface.h"
#include "Core/api/ReturnTypeCreator.h"
#include "CLI/States/Command/AddTaskCommand.h"
#include "CLI/Namespaces/CommandMapCreator.h"
#include "CLI/Model/ConsoleContext.h"

using ::testing::Return;

class AddTaskTest : public ::testing::Test {
public:
    AddTaskCommand state_;
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
    MOCK_METHOD(AddTaskResult, addTask, (const ServiceTaskDTO&), (override));
    MOCK_METHOD(AddTaskResult, addSubtask, (TaskID, const ServiceTaskDTO &), (override));
    MOCK_METHOD(RequstTaskResult, deleteTask, (TaskID), (override));
    MOCK_METHOD(RequstTaskResult, complete, (TaskID), (override));
    MOCK_METHOD(RequstTaskResult, postponeTask, (TaskID, boost::gregorian::date), (override));
    MOCK_METHOD(RequstTaskResult, editTask, (TaskID id, const ServiceTaskDTO&), (override));
public:

    MOCK_METHOD(std::vector<ServiceTaskDTO>, getSubtasks, (TaskID), (override));
    MOCK_METHOD(std::vector<ServiceTaskDTO>, getAllTasksByPriority, (), (override));
    MOCK_METHOD(std::vector<ServiceTaskDTO>, getTasksForToday, (), (override));
    MOCK_METHOD(std::vector<ServiceTaskDTO>, getTasksForWeek, (), (override));
    MOCK_METHOD(std::optional<ServiceTaskDTO>, getTask, (TaskID), (override));

private:
    MOCK_METHOD(bool, removeTask, (const std::weak_ptr<FullTask> &), (override));
};


TEST_F(AddTaskTest, shouldRead1) {
    auto io = std::make_unique<MockConsoleIO>();
    EXPECT_EQ(state_.read(*io), CommandState::Type::Option);
}

TEST_F(AddTaskTest, shouldRead2) {
    auto io = std::make_unique<MockConsoleIO>();
    EXPECT_NE(state_.read(*io), CommandState::Type::AddTask);
}


TEST_F(AddTaskTest, shouldPrint) {
    auto io = std::make_unique<MockConsoleIO>();
    EXPECT_NO_THROW(state_.print(*io));
}


TEST_F(AddTaskTest, shouldChange1) {
    auto io = std::make_unique<MockConsoleIO>();
    auto command_map = CommandMap::create();
    auto type = CommandState::Type::AddTask;
    EXPECT_EQ(state_.change(type)->read(*io), command_map[type]->read(*io));
}

TEST_F(AddTaskTest, shouldChange2) {
    auto io = std::make_unique<MockConsoleIO>();
    auto command_map = CommandMap::create();
    EXPECT_CALL(*io, input)
            .Times(1)
            .WillOnce(Return("add task"));
    auto type = CommandState::Type::Option;
    EXPECT_EQ(state_.change(type)->read(*io), CommandState::Type::AddTask);
}

TEST_F(AddTaskTest, shouldChange3) {
    auto command_map = CommandMap::create();
    auto type = CommandState::Type::Error;
    EXPECT_EQ(state_.change(type), command_map[type]);
}
TEST_F(AddTaskTest, shouldExecute) {
    auto io = std::make_unique<MockConsoleIO>();
    auto service = std::make_unique<MockTaskService>();
    auto &ref_to_service = *service;
    auto context = std::make_unique<ConsoleContext>(ConsoleContext::create(std::move(service)));

    EXPECT_CALL(*io, input)
            .Times(4)
            .WillOnce(Return("go to the gym"))
            .WillOnce(Return("sport"))
            .WillOnce(Return("2020-10-10"))
            .WillOnce(Return("2"));
    EXPECT_CALL(*io, output)
            .Times(5)
            .WillRepeatedly(Return());
    EXPECT_CALL(ref_to_service, addTask)
            .Times(1)
            .WillOnce(Return(operation_result::TaskAddedSuccessful(TaskID::create(5))));

    EXPECT_NO_THROW(state_.execute(*io, *context));
}

