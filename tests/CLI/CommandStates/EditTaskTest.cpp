//
// Created by Илля on 19.09.2020.
//

//
// Created by Илля on 19.09.2020.
//

#include <gtest/gtest.h>
#include "Mock/ConsoleIOMock.h"
#include "Mock/ServiceMock.h"
#include "CLI/States/Command/EditTaskCommand.h"
#include "CLI/Namespaces/CommandMapCreator.h"
#include "CLI/Model/ConsoleContext.h"

using ::testing::Return;

class EditTaskTest : public ::testing::Test {
public:
    EditTaskCommand state_;
    void SetUp() override{
    }
};

TEST_F(EditTaskTest, shouldRead1) {
    auto io = std::make_unique<MockConsoleIO>();
    EXPECT_EQ(state_.read(*io), CommandState::Type::Edit);
}

TEST_F(EditTaskTest, shouldRead2) {
    auto io = std::make_unique<MockConsoleIO>();
    EXPECT_NE(state_.read(*io), CommandState::Type::CompleteTask);
}


TEST_F(EditTaskTest, shouldPrint) {
    auto io = std::make_unique<MockConsoleIO>();
    EXPECT_NO_THROW(state_.print(*io));
}


TEST_F(EditTaskTest, shouldChange1) {
    auto io = std::make_unique<MockConsoleIO>();
    auto command_map = CommandMap::create();
    auto type = CommandState::Type::CompleteTask;
    EXPECT_CALL(*io, input)
            .Times(1)
            .WillOnce(Return("add subtask"));
    EXPECT_EQ(state_.change(type)->read(*io), CommandState::Type::AddSubtask);
}

TEST_F(EditTaskTest, shouldChange2) {
    auto io = std::make_unique<MockConsoleIO>();
    auto command_map = CommandMap::create();
    EXPECT_CALL(*io, input)
            .Times(1)
            .WillOnce(Return("add task"));
    auto type = CommandState::Type::Option;
    EXPECT_EQ(state_.change(type)->read(*io), CommandState::Type::AddTask);
}

TEST_F(EditTaskTest, shouldExecute) {
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

