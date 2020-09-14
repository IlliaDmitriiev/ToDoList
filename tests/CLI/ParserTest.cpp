//
// Created by hp on 09.09.2020.
//

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "CLI/States/Parse/Parser.h"

using ::testing::Return;

class ParserTest : public ::testing::Test {
public:
    Buffer buffer;
};


class MockConsoleIO : public IO {
public:
    MOCK_METHOD(std::string, input, (), (override));
    MOCK_METHOD(void, output, (std::string), (override));
};

TEST_F(ParserTest, shouldParseName) {

    auto io = std::make_unique<MockConsoleIO>();

    EXPECT_CALL(*io, output)
            .Times(1)
            .WillOnce(Return());

    EXPECT_CALL(*io, input)
            .Times(1)
            .WillOnce(Return("go to the club"));

    EXPECT_TRUE(Parser::parse(*io, buffer, Parser::Type::Name));
}

TEST_F(ParserTest, shouldParseLabel) {

    auto io = std::make_unique<MockConsoleIO>();

    EXPECT_CALL(*io, output)
            .Times(1)
            .WillOnce(Return());

    EXPECT_CALL(*io, input)
            .Times(1)
            .WillOnce(Return("party"));

    EXPECT_TRUE(Parser::parse(*io, buffer, Parser::Type::Label));
}

TEST_F(ParserTest, shouldParseID) {

    auto io = std::make_unique<MockConsoleIO>();

    EXPECT_CALL(*io, output)
            .Times(1)
            .WillOnce(Return());

    EXPECT_CALL(*io, input)
            .Times(1)
            .WillOnce(Return("1589"));

    EXPECT_TRUE(Parser::parse(*io, buffer, Parser::Type::ID));
}

TEST_F(ParserTest, shouldNotParseID) {

    auto io = std::make_unique<MockConsoleIO>();

    EXPECT_CALL(*io, output)
            .Times(1)
            .WillOnce(Return());

    EXPECT_CALL(*io, input)
            .Times(1)
            .WillOnce(Return("1gd fj fj1 8"));

    EXPECT_FALSE(Parser::parse(*io, buffer, Parser::Type::ID));

}

TEST_F(ParserTest, shouldParsePriority) {

    auto io = std::make_unique<MockConsoleIO>();

    EXPECT_CALL(*io, output)
            .Times(1)
            .WillOnce(Return());

    EXPECT_CALL(*io, input)
            .Times(1)
            .WillOnce(Return("3"));

    EXPECT_TRUE(Parser::parse(*io, buffer, Parser::Type::Priority));
}

TEST_F(ParserTest, shouldNotParsePriority1) {

    auto io = std::make_unique<MockConsoleIO>();

    EXPECT_CALL(*io, output)
            .Times(1)
            .WillOnce(Return());

    EXPECT_CALL(*io, input)
            .Times(1)
            .WillOnce(Return("5"));

    EXPECT_FALSE(Parser::parse(*io, buffer, Parser::Type::Priority));
}

TEST_F(ParserTest, shouldNotParsePriority2) {

    auto io = std::make_unique<MockConsoleIO>();

    EXPECT_CALL(*io, output)
            .Times(1)
            .WillOnce(Return());

    EXPECT_CALL(*io, input)
            .Times(1)
            .WillOnce(Return("fd j ru"));

    EXPECT_FALSE(Parser::parse(*io, buffer, Parser::Type::Priority));
}


TEST_F(ParserTest, shouldParseDate) {

    auto io = std::make_unique<MockConsoleIO>();

    EXPECT_CALL(*io, output)
            .Times(1)
            .WillOnce(Return());

    EXPECT_CALL(*io, input)
            .Times(1)
            .WillOnce(Return("2000-10-20"));

    EXPECT_TRUE(Parser::parse(*io, buffer, Parser::Type::Date));
}

TEST_F(ParserTest, shouldNotParseDate1) {

    auto io = std::make_unique<MockConsoleIO>();

    EXPECT_CALL(*io, output)
            .Times(1)
            .WillOnce(Return());

    EXPECT_CALL(*io, input)
            .Times(1)
            .WillOnce(Return("2000-10-32"));

    EXPECT_FALSE(Parser::parse(*io, buffer, Parser::Type::Date));
}


TEST_F(ParserTest, shouldNotParseDate2) {

    auto io = std::make_unique<MockConsoleIO>();

    EXPECT_CALL(*io, output)
            .Times(1)
            .WillOnce(Return());

    EXPECT_CALL(*io, input)
            .Times(1)
            .WillOnce(Return("2019-02-29"));

    EXPECT_FALSE(Parser::parse(*io, buffer, Parser::Type::Date));
}


TEST_F(ParserTest, shouldNotParseDate3) {

    auto io = std::make_unique<MockConsoleIO>();

    EXPECT_CALL(*io, output)
            .Times(1)
            .WillOnce(Return());

    EXPECT_CALL(*io, input)
            .Times(1)
            .WillOnce(Return("2000d dfyj "));

    EXPECT_FALSE(Parser::parse(*io, buffer, Parser::Type::Date));
}


TEST_F(ParserTest, shouldParseExit) {

    auto io = std::make_unique<MockConsoleIO>();

    EXPECT_FALSE(Parser::parse(*io, buffer, Parser::Type::Exit));
}

