//
// Created by illia on 14.08.20.
//

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "api/TaskService.h"
#include "api/TaskServiceCreator.h"

using ::testing::Return;
using ::testing::NiceMock;

class TaskServiceTest : public ::testing::Test {
public:
    void SetUp() override{

    }
};

class MockStorage : public TaskStorageInterface {

public:
    MOCK_METHOD(std::optional<std::weak_ptr<FullTask>>, getTask, (TaskID), (override));
    MOCK_METHOD(bool, addTask, (std::shared_ptr<FullTask>), (override));
    MOCK_METHOD(bool, deleteTask, (TaskID), (override));
    MOCK_METHOD(bool, deleteSubtaskInParent, (TaskID, TaskID), (override));
};

class MockView : public ViewInterface{

public:
    MOCK_METHOD(bool, addTask, (const std::weak_ptr<FullTask>&), (override));
    MOCK_METHOD(bool, deleteTask, (const std::weak_ptr<FullTask>&), (override));

    MOCK_METHOD(std::vector<std::weak_ptr<FullTask>>, getAllTasksByPrior, (),(override));
    MOCK_METHOD(std::vector<std::weak_ptr<FullTask>>, getTasksForToday, (boost::gregorian::date),(override));
    MOCK_METHOD(std::vector<std::weak_ptr<FullTask>>, getTasksForWeek, (boost::gregorian::date),(override));
};

TEST_F(TaskServiceTest, shouldAddTask) {
    std::vector ids = {TaskID::create(0), TaskID::create(2), TaskID::create(3), TaskID::create(4)};
}

TEST_F(TaskServiceTest, shouldPostponeTask) {
    auto viewByPriority = std::make_unique<MockView>();
    auto viewByDate = std::make_unique<MockView>();
    auto storage = std::make_unique<MockStorage>();

    TaskService ts(std::move(viewByPriority), std::move(viewByDate), std::move(storage));
    TaskDTO task = TaskDTO::create(boost::gregorian::date{2000,11,9}, "anme1", "w4re4", TaskPriority::First);

    AddTaskResult outcome  = ts.addTask(task);
    EXPECT_TRUE(outcome.id.has_value());
    RequstTaskResult requstTaskResult = ts.postponeTask(outcome.id.value(), boost::gregorian::date{2020,12,10});
    EXPECT_EQ(requstTaskResult.result, ResultType::SUCCESS);
}
