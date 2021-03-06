//
// Created by Илля on 19.09.2020.
//

#include <gtest/gtest.h>
#include "CLI/Mock/ConsoleIOMock.h"
#include "CLI/View/ParseStates/ParseName.h"

using ::testing::Return;

class ParseNameTest : public ::testing::Test {
public:
    ParseName state;
};

TEST_F(ParseNameTest, shouldRead) {
    auto buffer = ParameterStorage::create();
    auto io = std::make_unique<MockConsoleIO>();

    std::string name = "sdg dgh  4sfg 35 64";

    EXPECT_CALL(*io, input)
    .Times(1)
    .WillOnce(Return(name));

    EXPECT_TRUE(state.read(*io, buffer));
    EXPECT_EQ(buffer.getParameters().name_, name);
}

TEST_F(ParseNameTest, shouldPrint) {
    auto io = std::make_unique<MockConsoleIO>();

    EXPECT_CALL(*io, output)
            .Times(1)
            .WillOnce(Return());

    state.print(*io);
}

TEST_F(ParseNameTest, shouldChangeState) {

    EXPECT_EQ(state.changeState(), ParseState::Type::Name);
}


