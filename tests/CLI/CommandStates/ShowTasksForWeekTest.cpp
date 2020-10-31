
//
// Created by Илля on 19.09.2020.
//

#include <gtest/gtest.h>
#include "CLI/Mock/ConsoleIOMock.h"
#include "CLI/Mock/ServiceMock.h"
#include "CLI/View/CommandStates/ShowTasksForWeek.h"
#include "CLI/Utils/Creators/CommandMapCreator.h"
#include "CLI/Model/ConsoleContext.h"

using ::testing::Return;

class ShowTasksForWeekTest : public ::testing::Test {
public:
    ShowTasksForWeek state_;
    void SetUp() override{
    }
};

TEST_F(ShowTasksForWeekTest, shouldRead1) {
    auto io = std::make_unique<MockConsoleIO>();

    EXPECT_EQ(state_.read(*io), CommandState::Type::Submenu);
}

TEST_F(ShowTasksForWeekTest, shouldRead2) {
    auto io = std::make_unique<MockConsoleIO>();

    EXPECT_NE(state_.read(*io), CommandState::Type::DeleteTask);
}


TEST_F(ShowTasksForWeekTest, shouldPrint) {
    auto io = std::make_unique<MockConsoleIO>();

    EXPECT_NO_THROW(state_.print(*io));
}


TEST_F(ShowTasksForWeekTest, shouldChange1) {
    auto io = std::make_unique<MockConsoleIO>();
    auto command_map = CommandMap::create();
    auto type = CommandState::Type::CompleteTask;
    EXPECT_EQ(state_.change(type)->read(*io), CommandState::Type::Option);
}

TEST_F(ShowTasksForWeekTest, shouldChange2) {
    auto io = std::make_unique<MockConsoleIO>();
    auto command_map = CommandMap::create();

    auto type = CommandState::Type::AddTask;
    EXPECT_EQ(state_.change(type)->read(*io), CommandState::Type::Option);
}

TEST_F(ShowTasksForWeekTest, shouldExecute) {
    auto io = std::make_unique<MockConsoleIO>();
    auto service = std::make_unique<MockTaskService>();
    auto &ref_to_service = *service;
    auto context = std::make_unique<ConsoleContext>(ConsoleContext::create(std::move(service)));

    auto task1 = TaskDTO::create(TaskID::create(0),boost::gregorian::date(2020, 10, 10),"name1","label1",TaskPriority::None, false);
    auto task2 = TaskDTO::create(TaskID::create(0),boost::gregorian::date(2010, 10, 10),"name2","label2",TaskPriority::First, true);
    auto task3 = TaskDTO::create(TaskID::create(0),boost::gregorian::date(2222, 02, 22),"name3","label3",TaskPriority::First, false);
    std::vector<TaskDTO> v{task1, task2, task3};

    EXPECT_CALL(ref_to_service, getTasksForWeek)
            .Times(1)
            .WillOnce(Return(v));
    EXPECT_CALL(*io, output)
            .Times(4)
            .WillRepeatedly(Return());

    EXPECT_NO_THROW(state_.execute(*io, *context));
}

