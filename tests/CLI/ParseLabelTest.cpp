//
// Created by Илля on 19.09.2020.
//

#include <gtest/gtest.h>
#include "CLI/Mock/ConsoleIOMock.h"
#include "CLI/States/Parse/ParseLabel.h"

using ::testing::Return;

class ParseLabelTest : public ::testing::Test {
public:
    ParseLabel state;
};

TEST_F(ParseLabelTest, shouldRead) {
    auto buffer = ParameterStorage::create();
    auto io = std::make_unique<MockConsoleIO>();

    std::string label = "sport  at home";

    EXPECT_CALL(*io, input)
            .Times(1)
            .WillOnce(Return(label));

    EXPECT_TRUE(state.read(*io, buffer));
    EXPECT_EQ(buffer.getParameters().label_, label);
}

TEST_F(ParseLabelTest, shouldPrint) {
    auto io = std::make_unique<MockConsoleIO>();

    EXPECT_CALL(*io, output)
            .Times(1)
            .WillOnce(Return());

    state.print(*io);
}

TEST_F(ParseLabelTest, shouldReturnLabel1) {
    EXPECT_EQ(state.changeState(), ParseState::Type::Label);
}

TEST_F(ParseLabelTest, shouldReturnLabel2) {
    EXPECT_NE(state.changeState(), ParseState::Type::Name);
}


