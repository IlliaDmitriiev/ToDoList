//
// Created by hp on 09.09.2020.
//

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "CLI/Controller/ParseMachine.h"

using ::testing::Return;

class ParseMachineTest : public ::testing::Test {
public:
    Buffer buffer;
};


class MockConsoleIO : public IO {
public:
    MOCK_METHOD(std::string, input, (), (override));
    MOCK_METHOD(void, output, (std::string), (override));
};

TEST_F(ParseMachineTest, shouldParseGraph1) {

    auto io = std::make_unique<MockConsoleIO>();

    EXPECT_CALL(*io, output)
            .Times(2)
            .WillRepeatedly(Return());

    EXPECT_CALL(*io, input)
            .Times(2)
            .WillOnce(Return("124587"))
            .WillOnce(Return("2000-10-10"));

    std::map<Parser::Type, Parser::Type> links{
            {Parser::Type::ID, Parser::Type::Date},
            {Parser::Type::Date, Parser::Type::Exit},
    };

    ParseMachine pm(*io, buffer, Parser::Type::ID, links);
    pm.run();

}

TEST_F(ParseMachineTest, shouldParseGraph2) {

    auto io = std::make_unique<MockConsoleIO>();

    EXPECT_CALL(*io, output)
            .Times(4)
            .WillRepeatedly(Return());

    EXPECT_CALL(*io, input)
            .Times(3)
            .WillOnce(Return("1 dg hfj f"))
            .WillOnce(Return("1"))
            .WillOnce(Return("simple name"));

    std::map<Parser::Type, Parser::Type> links{
            {Parser::Type::Priority, Parser::Type::Name},
            {Parser::Type::Name, Parser::Type::Exit},
    };

    ParseMachine pm(*io, buffer, Parser::Type::ID, links);
    pm.run();

}

TEST_F(ParseMachineTest, shouldParseEmptyGraph) {

    auto io = std::make_unique<MockConsoleIO>();
    std::map<Parser::Type, Parser::Type> links;

    ParseMachine pm(*io, buffer, Parser::Type::Label, links);
    pm.run();

}
