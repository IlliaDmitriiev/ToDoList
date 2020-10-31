//
// Created by Илля on 19.09.2020.
//

//
// Created by Илля on 19.09.2020.
//

#include <gtest/gtest.h>
#include "CLI/Mock/ConsoleIOMock.h"
#include "CLI/Mock/ServiceMock.h"
#include "CLI/States/Command/PostponeTaskCommand.h"
#include "CLI/Namespaces/CommandMapCreator.h"
#include "CLI/Model/ConsoleContext.h"

using ::testing::Return;

class PostponeTaskTest : public ::testing::Test {
public:
    PostponeTaskCommand state_;
    void SetUp() override{
    }
};

TEST_F(PostponeTaskTest, shouldRead1) {
    auto io = std::make_unique<MockConsoleIO>();
    EXPECT_EQ(state_.read(*io), CommandState::Type::Option);
}

TEST_F(PostponeTaskTest, shouldRead2) {
    auto io = std::make_unique<MockConsoleIO>();
    EXPECT_NE(state_.read(*io), CommandState::Type::CompleteTask);
}


TEST_F(PostponeTaskTest, shouldPrint) {
    auto io = std::make_unique<MockConsoleIO>();
    EXPECT_NO_THROW(state_.print(*io));
}


TEST_F(PostponeTaskTest, shouldChange1) {
    auto io = std::make_unique<MockConsoleIO>();
    auto command_map = CommandMap::create();
    auto type = CommandState::Type::CompleteTask;

    EXPECT_EQ(state_.change(type)->read(*io), CommandState::Type::Option);
}

TEST_F(PostponeTaskTest, shouldChange2) {
    auto io = std::make_unique<MockConsoleIO>();
    auto command_map = CommandMap::create();
    EXPECT_CALL(*io, input)
            .Times(1)
            .WillOnce(Return("add task"));
    auto type = CommandState::Type::Option;
    EXPECT_EQ(state_.change(type)->read(*io), CommandState::Type::AddTask);
}

TEST_F(PostponeTaskTest, shouldExecute) {
    auto io = std::make_unique<MockConsoleIO>();
    auto service = std::make_unique<MockTaskService>();
    auto &ref_to_service = *service;
    auto context = std::make_unique<ConsoleContext>(ConsoleContext::create(std::move(service)));

    EXPECT_CALL(*io, input)
            .Times(2)
            .WillOnce(Return("57"))
            .WillOnce(Return("2020-10-10"));
    EXPECT_CALL(*io, output)
            .Times(3)
            .WillRepeatedly(Return());

    EXPECT_NO_THROW(state_.execute(*io, *context));
}

