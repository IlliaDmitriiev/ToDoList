//
// Created by ilya on 13.10.2020.
//

#include <gtest/gtest.h>
#include "CLI/Mock/ConsoleIOMock.h"
#include "CLI/States/Parse/ParseFilename.h"

using ::testing::Return;

class ParseFilenameTest : public ::testing::Test {
public:
    ParseFilename state;
};

TEST_F(ParseFilenameTest, shouldReadSuccessfully) {
    auto buffer = ParameterStorage::create();
    auto io = std::make_unique<MockConsoleIO>();

    std::string name = "sdg dgh  4sfg 35 64";

    EXPECT_CALL(*io, input)
    .Times(1)
    .WillOnce(Return(name));

    EXPECT_TRUE(state.read(*io, buffer));
    EXPECT_EQ(buffer.getParameters().filename_, name);
}

TEST_F(ParseFilenameTest, shouldReadUnsuccessfully) {
    auto buffer = ParameterStorage::create();
    auto io = std::make_unique<MockConsoleIO>();

    std::string name = "";

    EXPECT_CALL(*io, input)
            .Times(1)
            .WillOnce(Return(name));

    EXPECT_FALSE(state.read(*io, buffer));
    EXPECT_EQ(buffer.getParameters().filename_, name);
}

TEST_F(ParseFilenameTest, shouldPrint) {
    auto io = std::make_unique<MockConsoleIO>();

    EXPECT_CALL(*io, output)
    .Times(1)
    .WillOnce(Return());

    EXPECT_NO_THROW(state.print(*io));
}

TEST_F(ParseFilenameTest, shouldChangeState) {
    EXPECT_EQ(state.changeState(), ParseState::Type::Filename);
}