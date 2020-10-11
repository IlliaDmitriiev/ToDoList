//
// Created by ilya on 11.10.2020.
//
#include <gtest/gtest.h>
#include "Mock/ConsoleIOMock.h"
#include "Mock/ServiceMock.h"
#include "CLI/States/Command/SaveCommand.h"
#include "CLI/Namespaces/CommandMapCreator.h"
#include "CLI/Model/ConsoleContext.h"

using ::testing::Return;

class SaveTest : public ::testing::Test {
public:
    SaveCommand state_;
    void SetUp() override{
    }
};

TEST_F(SaveTest, shouldRead1) {
    auto io = std::make_unique<MockConsoleIO>();
    EXPECT_EQ(state_.read(*io), CommandState::Type::Option);
}

TEST_F(SaveTest, shouldRead2) {
    auto io = std::make_unique<MockConsoleIO>();
    EXPECT_NE(state_.read(*io), CommandState::Type::CompleteTask);
}


TEST_F(SaveTest, shouldPrint) {
    auto io = std::make_unique<MockConsoleIO>();
    EXPECT_NO_THROW(state_.print(*io));
}


TEST_F(SaveTest, shouldChange1) {
    auto io = std::make_unique<MockConsoleIO>();
    auto command_map = CommandMap::create();
    auto type = CommandState::Type::CompleteTask;
    EXPECT_EQ(state_.change(type)->read(*io), command_map[type]->read(*io));
}

TEST_F(SaveTest, shouldChange2) {
    auto io = std::make_unique<MockConsoleIO>();
    auto command_map = CommandMap::create();
    EXPECT_CALL(*io, input)
            .Times(1)
            .WillOnce(Return("add task"));
    auto type = CommandState::Type::Option;
    EXPECT_EQ(state_.change(type)->read(*io), CommandState::Type::AddTask);
}

TEST_F(SaveTest, shouldChange3) {
    auto command_map = CommandMap::create();
    auto type = CommandState::Type::Error;
    EXPECT_EQ(state_.change(type), command_map[type]);
}

TEST_F(SaveTest, shouldExecuteSuccessfully) {
    auto io = std::make_unique<MockConsoleIO>();
    auto service = std::make_unique<MockTaskService>();

    EXPECT_CALL(*io, output)
            .Times(1)
            .WillOnce(Return());
    EXPECT_CALL(*service, save)
            .Times(1)
            .WillOnce(Return(operation_result::TaskRequestedSuccessful()));

    auto context = std::make_unique<ConsoleContext>(ConsoleContext::create(std::move(service)));

    EXPECT_NO_THROW(state_.execute(*io, *context));
}

TEST_F(SaveTest, shouldExecuteUnsuccessfully) {
    auto io = std::make_unique<MockConsoleIO>();
    auto service = std::make_unique<MockTaskService>();

    EXPECT_CALL(*io, output)
            .Times(1)
            .WillOnce(Return());
    EXPECT_CALL(*service, save)
            .Times(1)
            .WillOnce(Return(operation_result::TaskRequestedSuccessful()));

    auto context = std::make_unique<ConsoleContext>(ConsoleContext::create(std::move(service)));

    EXPECT_NO_THROW(state_.execute(*io, *context));
}
