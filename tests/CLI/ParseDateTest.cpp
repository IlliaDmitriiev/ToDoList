//
// Created by Илля on 19.09.2020.
//

#include <gtest/gtest.h>
#include "CLI/Mock/ConsoleIOMock.h"
#include "CLI/View/ParseStates/ParseDate.h"

using ::testing::Return;

class ParseDateTest : public ::testing::Test {
public:
    ParseDate state;
};

TEST_F(ParseDateTest, shouldRead1) {
    auto buffer = ParameterStorage::create();
    auto io = std::make_unique<MockConsoleIO>();

    std::string date = "ssg dh fyh";

    EXPECT_CALL(*io, input)
            .Times(1)
            .WillOnce(Return(date));

    EXPECT_FALSE(state.read(*io, buffer));
}

TEST_F(ParseDateTest, shouldRead2) {
    auto buffer = ParameterStorage::create();
    auto io = std::make_unique<MockConsoleIO>();

    std::string date = "-55";

    EXPECT_CALL(*io, input)
            .Times(1)
            .WillOnce(Return(date));

    EXPECT_FALSE(state.read(*io, buffer));
}

TEST_F(ParseDateTest, shouldRead3) {
    auto buffer = ParameterStorage::create();
    auto io = std::make_unique<MockConsoleIO>();

    std::string date = "2019-02-29";

    EXPECT_CALL(*io, input)
            .Times(1)
            .WillOnce(Return(date));

    EXPECT_FALSE(state.read(*io, buffer));
}

TEST_F(ParseDateTest, shouldRead4) {
    auto buffer = ParameterStorage::create();
    auto io = std::make_unique<MockConsoleIO>();

    std::string date = "2020-10-10";

    EXPECT_CALL(*io, input)
            .Times(1)
            .WillOnce(Return(date));

    EXPECT_TRUE(state.read(*io, buffer));
    EXPECT_EQ(buffer.getParameters().date_, boost::gregorian::from_string(date));
}

TEST_F(ParseDateTest, shouldPrint) {
    auto io = std::make_unique<MockConsoleIO>();

    EXPECT_CALL(*io, output)
            .Times(1)
            .WillOnce(Return());

    state.print(*io);
}

TEST_F(ParseDateTest, shouldReturnID1) {
    EXPECT_EQ(state.changeState(), ParseState::Type::Date);
}

TEST_F(ParseDateTest, shouldReturnID2) {
    EXPECT_NE(state.changeState(), ParseState::Type::Name);
}


