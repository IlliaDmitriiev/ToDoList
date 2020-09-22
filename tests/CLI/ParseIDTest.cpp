//
// Created by Илля on 19.09.2020.
//

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "CLI/States/Parse/ParseID.h"

using ::testing::Return;

class ParseIDTest : public ::testing::Test {
public:
    ParseID state;
};


class MockConsoleIO : public IO {
public:
    MOCK_METHOD(std::string, input, (), (override));
    MOCK_METHOD(void, output, (std::string), (override));
};

TEST_F(ParseIDTest, shouldRead1) {
    auto buffer = ParameterStorage::create();
    auto io = std::make_unique<MockConsoleIO>();

    std::string id = "ssg dh fyh";

    EXPECT_CALL(*io, input)
            .Times(1)
            .WillOnce(Return(id));

    EXPECT_FALSE(state.read(*io, buffer));
}

TEST_F(ParseIDTest, shouldRead2) {
    auto buffer = ParameterStorage::create();
    auto io = std::make_unique<MockConsoleIO>();

    std::string id = "-5";

    EXPECT_CALL(*io, input)
            .Times(1)
            .WillOnce(Return(id));

    EXPECT_FALSE(state.read(*io, buffer));
}

TEST_F(ParseIDTest, shouldRead3) {
    auto buffer = ParameterStorage::create();
    auto io = std::make_unique<MockConsoleIO>();

    std::string id = "1 1 1 1 1178";

    EXPECT_CALL(*io, input)
            .Times(1)
            .WillOnce(Return(id));

    EXPECT_FALSE(state.read(*io, buffer));
}

TEST_F(ParseIDTest, shouldRead4) {
    auto buffer = ParameterStorage::create();
    auto io = std::make_unique<MockConsoleIO>();

    std::string id = "120";

    EXPECT_CALL(*io, input)
            .Times(1)
            .WillOnce(Return(id));

    EXPECT_TRUE(state.read(*io, buffer));
    EXPECT_EQ(buffer.getParameters().id_, std::stoi(id));
}

TEST_F(ParseIDTest, shouldPrint) {
    auto io = std::make_unique<MockConsoleIO>();

    EXPECT_CALL(*io, output)
            .Times(1)
            .WillOnce(Return());

    state.print(*io);
}

TEST_F(ParseIDTest, shouldReturnID1) {
    EXPECT_EQ(state.changeState(), ParseState::Type::ID);
}

TEST_F(ParseIDTest, shouldReturnID2) {
    EXPECT_NE(state.changeState(), ParseState::Type::Name);
}


