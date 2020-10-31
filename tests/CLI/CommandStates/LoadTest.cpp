//
// Created by ilya on 11.10.2020.
//

#include <gtest/gtest.h>
#include "CLI/Mock/ConsoleIOMock.h"
#include "CLI/Mock/ServiceMock.h"
#include "CLI/View/CommandStates/LoadCommand.h"
#include "CLI/Utils/Creators/CommandMapCreator.h"
#include "CLI/Model/ConsoleContext.h"

using ::testing::Return;

class LoadTest : public ::testing::Test {
public:
    LoadCommand state_;
    void SetUp() override{
    }
};

TEST_F(LoadTest, shouldRead1) {
    auto io = std::make_unique<MockConsoleIO>();
    EXPECT_EQ(state_.read(*io), CommandState::Type::Option);
}

TEST_F(LoadTest, shouldRead2) {
    auto io = std::make_unique<MockConsoleIO>();
    EXPECT_NE(state_.read(*io), CommandState::Type::CompleteTask);
}


TEST_F(LoadTest, shouldPrint) {
    auto io = std::make_unique<MockConsoleIO>();
    EXPECT_NO_THROW(state_.print(*io));
}


TEST_F(LoadTest, shouldChange1) {
    auto io = std::make_unique<MockConsoleIO>();
    auto command_map = CommandMap::create();
    auto type = CommandState::Type::CompleteTask;
    EXPECT_EQ(state_.change(type)->read(*io), command_map[type]->read(*io));
}

TEST_F(LoadTest, shouldChange2) {
    auto io = std::make_unique<MockConsoleIO>();
    auto command_map = CommandMap::create();
    EXPECT_CALL(*io, input)
            .Times(1)
            .WillOnce(Return("add task"));
    auto type = CommandState::Type::Option;
    EXPECT_EQ(state_.change(type)->read(*io), CommandState::Type::AddTask);
}

TEST_F(LoadTest, shouldChange3) {
    auto command_map = CommandMap::create();
    auto type = CommandState::Type::Error;
    EXPECT_EQ(state_.change(type), command_map[type]);
}

TEST_F(LoadTest, shouldExecuteSuccessfully) {
    auto io = std::make_unique<MockConsoleIO>();
    auto service = std::make_unique<MockTaskService>();

    EXPECT_CALL(*io, input)
            .Times(1)
            .WillOnce(Return("filename"));
    EXPECT_CALL(*io, output)
            .Times(2)
            .WillRepeatedly(Return());
    EXPECT_CALL(*service, load)
            .Times(1)
            .WillOnce(Return(operation_result::TaskRequestedSuccessful()));

    auto context = std::make_unique<ConsoleContext>(ConsoleContext::create(std::move(service)));

    EXPECT_NO_THROW(state_.execute(*io, *context));
}

TEST_F(LoadTest, shouldExecuteUnsuccessfully) {
    auto io = std::make_unique<MockConsoleIO>();
    auto service = std::make_unique<MockTaskService>();

    EXPECT_CALL(*io, input)
            .Times(1)
            .WillOnce(Return("filename"));
    EXPECT_CALL(*io, output)
            .Times(2)
            .WillRepeatedly(Return());
    EXPECT_CALL(*service, load)
            .Times(1)
            .WillOnce(Return(operation_result::TaskRequestedSuccessful()));

    auto context = std::make_unique<ConsoleContext>(ConsoleContext::create(std::move(service)));

    EXPECT_NO_THROW(state_.execute(*io, *context));
}
