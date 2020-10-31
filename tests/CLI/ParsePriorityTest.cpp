//
// Created by Илля on 19.09.2020.
//

#include <gtest/gtest.h>
#include "CLI/Mock/ConsoleIOMock.h"
#include "CLI/States/Parse/ParsePriority.h"

using ::testing::Return;

class ParsePriorityTest : public ::testing::Test {
public:
    ParsePriority state;
};

TEST_F(ParsePriorityTest, shouldRead1) {
    auto buffer = ParameterStorage::create();
    auto io = std::make_unique<MockConsoleIO>();

    std::string priority = "ssg dh fyh";

    EXPECT_CALL(*io, input)
            .Times(1)
            .WillOnce(Return(priority));

    EXPECT_FALSE(state.read(*io, buffer));
}

TEST_F(ParsePriorityTest, shouldRead2) {
    auto buffer = ParameterStorage::create();
    auto io = std::make_unique<MockConsoleIO>();

    std::string priority = "-0";

    EXPECT_CALL(*io, input)
            .Times(1)
            .WillOnce(Return(priority));

    EXPECT_FALSE(state.read(*io, buffer));
}

TEST_F(ParsePriorityTest, shouldRead3) {
    auto buffer = ParameterStorage::create();
    auto io = std::make_unique<MockConsoleIO>();

    std::string priority = "5";

    EXPECT_CALL(*io, input)
            .Times(1)
            .WillOnce(Return(priority));

    EXPECT_FALSE(state.read(*io, buffer));
}

TEST_F(ParsePriorityTest, shouldRead4) {
    auto buffer = ParameterStorage::create();
    auto io = std::make_unique<MockConsoleIO>();

    std::string priority = "4";

    EXPECT_CALL(*io, input)
            .Times(1)
            .WillOnce(Return(priority));

    EXPECT_TRUE(state.read(*io, buffer));
    EXPECT_EQ(buffer.getParameters().priority_, (TaskPriority)(std::stoi(priority) % 4));
}

TEST_F(ParsePriorityTest, shouldPrint) {
    auto io = std::make_unique<MockConsoleIO>();

    EXPECT_CALL(*io, output)
            .Times(1)
            .WillOnce(Return());

    state.print(*io);
}

TEST_F(ParsePriorityTest, shouldReturnID1) {
    EXPECT_EQ(state.changeState(), ParseState::Type::Priority);
}

TEST_F(ParsePriorityTest, shouldReturnID2) {
    EXPECT_NE(state.changeState(), ParseState::Type::Name);
}


