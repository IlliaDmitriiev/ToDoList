//
// Created by Илля on 19.09.2020.
//

//
// Created by Илля on 19.09.2020.
//

#include <gtest/gtest.h>
#include "CLI/Mock/ConsoleIOMock.h"
#include "CLI/Mock/ServiceMock.h"
#include "CLI/States/Command/CommandOption.h"
#include "CLI/Namespaces/CommandMapCreator.h"
#include "CLI/Model/ConsoleContext.h"

using ::testing::Return;

class OptionTest : public ::testing::Test {
public:
    CommandOption state_;
    void SetUp() override{
    }
};

TEST_F(OptionTest, shouldRead1) {
    auto io = std::make_unique<MockConsoleIO>();
    EXPECT_CALL(*io, input)
            .Times(1)
            .WillOnce(Return("add subtask"));
    EXPECT_EQ(state_.read(*io), CommandState::Type::AddSubtask);
}

TEST_F(OptionTest, shouldRead2) {
    auto io = std::make_unique<MockConsoleIO>();
    EXPECT_CALL(*io, input)
            .Times(1)
            .WillOnce(Return("complete task"));
    EXPECT_NE(state_.read(*io), CommandState::Type::DeleteTask);
}


TEST_F(OptionTest, shouldPrint) {
    auto io = std::make_unique<MockConsoleIO>();
    EXPECT_CALL(*io, output)
            .Times(1)
            .WillOnce(Return());
    EXPECT_NO_THROW(state_.print(*io));
}


TEST_F(OptionTest, shouldChange1) {
    auto io = std::make_unique<MockConsoleIO>();
    auto command_map = CommandMap::create();
    auto type = CommandState::Type::CompleteTask;
    EXPECT_EQ(state_.change(type)->read(*io), CommandState::Type::Option);
}

TEST_F(OptionTest, shouldChange2) {
    auto io = std::make_unique<MockConsoleIO>();
    auto command_map = CommandMap::create();

    auto type = CommandState::Type::AddTask;
    EXPECT_EQ(state_.change(type)->read(*io), CommandState::Type::Option);
}

TEST_F(OptionTest, shouldExecute) {
    auto io = std::make_unique<MockConsoleIO>();
    auto service = std::make_unique<MockTaskService>();
    auto &ref_to_service = *service;
    auto context = std::make_unique<ConsoleContext>(ConsoleContext::create(std::move(service)));

    EXPECT_NO_THROW(state_.execute(*io, *context));
}

