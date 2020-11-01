//
// Created by Илля on 19.09.2020.
//

#include <gtest/gtest.h>
#include "CLI/Mock/ConsoleIOMock.h"
#include "CLI/Mock/ServiceMock.h"
#include "CLI/View/CommandStates/AddTaskCommand.h"
#include "CLI/Utils/Creators/CommandMapCreator.h"
#include "CLI/Model/ConsoleContext.h"

using ::testing::Return;

class AddTaskTest : public ::testing::Test {
public:
    AddTaskCommand state_;
    void SetUp() override{
    }
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

