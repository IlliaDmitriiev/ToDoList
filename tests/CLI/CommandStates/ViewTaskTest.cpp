//
// Created by Илля on 19.09.2020.
//

#include <gtest/gtest.h>
#include "Mock/ConsoleIOMock.h"
#include "Mock/ServiceMock.h"
#include "CLI/States/Command/ViewTaskCommand.h"
#include "CLI/Namespaces/CommandMapCreator.h"
#include "CLI/Model/ConsoleContext.h"

using ::testing::Return;

class ViewTaskTest : public ::testing::Test {
public:
    ViewTaskCommand state_;
    void SetUp() override{
    }
};

TEST_F(ViewTaskTest, shouldRead1) {
    auto io = std::make_unique<MockConsoleIO>();
    EXPECT_EQ(state_.read(*io), CommandState::Type::View);
}

TEST_F(ViewTaskTest, shouldRead2) {
    auto io = std::make_unique<MockConsoleIO>();
    EXPECT_NE(state_.read(*io), CommandState::Type::CompleteTask);
}


TEST_F(ViewTaskTest, shouldPrint) {
    auto io = std::make_unique<MockConsoleIO>();
    EXPECT_NO_THROW(state_.print(*io));
}


TEST_F(ViewTaskTest, shouldChange1) {
    auto io = std::make_unique<MockConsoleIO>();
    auto command_map = CommandMap::create();
    auto type = CommandState::Type::CompleteTask;
    EXPECT_CALL(*io, input)
            .Times(1)
            .WillOnce(Return("add subtask"));
    EXPECT_EQ(state_.change(type)->read(*io), CommandState::Type::AddSubtask);
}

TEST_F(ViewTaskTest, shouldChange2) {
    auto io = std::make_unique<MockConsoleIO>();
    auto command_map = CommandMap::create();
    EXPECT_CALL(*io, input)
            .Times(1)
            .WillOnce(Return("add task"));
    auto type = CommandState::Type::Option;
    EXPECT_EQ(state_.change(type)->read(*io), CommandState::Type::AddTask);
}

TEST_F(ViewTaskTest, shouldExecute) {
    auto io = std::make_unique<MockConsoleIO>();
    auto service = std::make_unique<MockTaskService>();
    auto &ref_to_service = *service;
    auto context = std::make_unique<ConsoleContext>(ConsoleContext::create(std::move(service)));

    EXPECT_CALL(*io, input)
            .Times(1)
            .WillOnce(Return("47"));

    EXPECT_CALL(*io, output)
            .Times(2)
            .WillRepeatedly(Return());

    EXPECT_NO_THROW(state_.execute(*io, *context));
}

