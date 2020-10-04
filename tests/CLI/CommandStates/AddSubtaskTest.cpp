//
// Created by Илля on 19.09.2020.
//

#include <gtest/gtest.h>
#include "Mock/ConsoleIOMock.h"
#include "Mock/ServiceMock.h"
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

