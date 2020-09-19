//
// Created by hp on 09.09.2020.
//

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "CLI/Controller/ParseMachine.h"

using ::testing::Return;

class ParseMachineTest : public ::testing::Test {
    
};


class MockConsoleIO : public IO {
public:
    MOCK_METHOD(std::string, input, (), (override));
    MOCK_METHOD(void, output, (std::string), (override));
};

TEST_F(ParseMachineTest, shouldParseGraph1) {
    auto buffer = ParameterStorage::create();
    auto io = std::make_unique<MockConsoleIO>();

    EXPECT_CALL(*io, output)
            .Times(2)
            .WillRepeatedly(Return());

    EXPECT_CALL(*io, input)
            .Times(2)
            .WillOnce(Return("124587"))
            .WillOnce(Return("2000-10-10"));

    std::map<ParseState::Type, ParseState::Type> links{
            {ParseState::Type::ID, ParseState::Type::Date},
            {ParseState::Type::Date, ParseState::Type::Exit},
    };

    ParseMachine pm(*io, buffer, ParseState::Type::ID, links);
    pm.run();

}

TEST_F(ParseMachineTest, shouldParseGraph2) {
    auto buffer = ParameterStorage::create();
    auto io = std::make_unique<MockConsoleIO>();

    EXPECT_CALL(*io, output)
            .Times(4)
            .WillRepeatedly(Return());

    EXPECT_CALL(*io, input)
            .Times(3)
            .WillOnce(Return("1 dg hfj f"))
            .WillOnce(Return("1"))
            .WillOnce(Return("simple name"));

    std::map<ParseState::Type, ParseState::Type> links{
            {ParseState::Type::Priority, ParseState::Type::Name},
            {ParseState::Type::Name, ParseState::Type::Exit},
    };

    ParseMachine pm(*io, buffer, ParseState::Type::Priority, links);
    pm.run();

}

TEST_F(ParseMachineTest, shouldParseEmptyGraph) {
    auto buffer = ParameterStorage::create();
    auto io = std::make_unique<MockConsoleIO>();
    std::map<ParseState::Type, ParseState::Type> links;

    ParseMachine pm(*io, buffer, ParseState::Type::Label, links);
    pm.run();

}
