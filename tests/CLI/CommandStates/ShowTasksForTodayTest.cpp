
//
// Created by Илля on 19.09.2020.
//

#include <gtest/gtest.h>
#include "Mock/ConsoleIOMock.h"
#include "Mock/ServiceMock.h"
#include "CLI/States/Command/ShowTasksForTodayCommand.h"
#include "CLI/Namespaces/CommandMapCreator.h"
#include "CLI/Model/ConsoleContext.h"

using ::testing::Return;

class ShowTasksForTodayTest : public ::testing::Test {
public:
    ShowTasksForTodayCommand state_;
    void SetUp() override{
    }
};

TEST_F(ShowTasksForTodayTest, shouldRead1) {
    auto io = std::make_unique<MockConsoleIO>();

    EXPECT_EQ(state_.read(*io), CommandState::Type::Submenu);
}

TEST_F(ShowTasksForTodayTest, shouldRead2) {
    auto io = std::make_unique<MockConsoleIO>();

    EXPECT_NE(state_.read(*io), CommandState::Type::DeleteTask);
}


TEST_F(ShowTasksForTodayTest, shouldPrint) {
    auto io = std::make_unique<MockConsoleIO>();

    EXPECT_NO_THROW(state_.print(*io));
}


TEST_F(ShowTasksForTodayTest, shouldChange1) {
    auto io = std::make_unique<MockConsoleIO>();
    auto command_map = CommandMap::create();
    auto type = CommandState::Type::CompleteTask;
    EXPECT_EQ(state_.change(type)->read(*io), CommandState::Type::Option);
}

TEST_F(ShowTasksForTodayTest, shouldChange2) {
    auto io = std::make_unique<MockConsoleIO>();
    auto command_map = CommandMap::create();

    auto type = CommandState::Type::AddTask;
    EXPECT_EQ(state_.change(type)->read(*io), CommandState::Type::Option);
}

TEST_F(ShowTasksForTodayTest, shouldExecute) {
    auto io = std::make_unique<MockConsoleIO>();
    auto service = std::make_unique<MockTaskService>();
    auto &ref_to_service = *service;
    auto context = std::make_unique<ConsoleContext>(ConsoleContext::create(std::move(service)));

    auto task1 = ServiceTaskDTO::create(boost::gregorian::date(2020, 10, 10),"name1","label1",TaskPriority::None);
    auto task2 = ServiceTaskDTO::create(boost::gregorian::date(2010, 10, 10),"name2","label2",TaskPriority::First);
    std::vector<ServiceTaskDTO> v{task1, task2};

    EXPECT_CALL(ref_to_service, getTasksForToday)
            .Times(1)
            .WillOnce(Return(v));
    EXPECT_CALL(*io, output)
            .Times(3)
            .WillRepeatedly(Return());

    EXPECT_NO_THROW(state_.execute(*io, *context));
}

