//
// Created by illia on 14.08.20.
//

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "api/TaskService.h"

using ::testing::Return;

class TaskServiceTest : public ::testing::Test {
public:
    std::shared_ptr<FullTask> shared_task1;
    std::shared_ptr<FullTask> shared_task2;
    std::shared_ptr<FullTask> shared_task3;
    std::shared_ptr<FullTask> shared_task4;

    void SetUp() override{
        time_t now = time(0);
        auto cur = std::make_unique<tm>(*gmtime(&now));
        boost::gregorian::date date1(cur->tm_year+1900, cur->tm_mon + 1, cur->tm_mday);
        boost::gregorian::date date2(date1.day_number() + 7 - (date1.day_of_week() + 7) % 7);

        const Task t1 = Task::create(
                date1,
                "name1",
                "",
                TaskPriority::None);

        const Task t2 = Task::create(
                date2,
                "name2",
                "456578y&#&@)(#$?><</*-+fdg",
                TaskPriority::Second);


        const Task t3 = Task::create(
                boost::gregorian::date(1500, 2, 26),
                "name3",
                "label3",
                TaskPriority::Third);

        const Task t4 = Task::create(
                date1,
                "name4",
                "",
                TaskPriority::First);
        FullTask task1 = FullTask::create(TaskID::create(0), t1);
        FullTask task2 = FullTask::create(TaskID::create(1), t2);
        FullTask task3 = FullTask::create(TaskID::create(2), t3);
        FullTask task4 = FullTask::create(TaskID::create(3), t4);

        shared_task1 = std::make_shared<FullTask>(task1);
        shared_task2 = std::make_shared<FullTask>(task2);
        shared_task3 = std::make_shared<FullTask>(task3);
        shared_task4 = std::make_shared<FullTask>(task4);
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


bool operator == (const std::weak_ptr<FullTask> task1, const std::weak_ptr<FullTask> task2){
    return task1.lock()->getId().getId()== task2.lock()->getId().getId();
}

bool operator == (const std::shared_ptr<FullTask> task1, const std::shared_ptr<FullTask> task2){
    return task1->getId().getId()== task2->getId().getId();
}

TEST_F(TaskServiceTest, shouldAddTask) {
    auto viewByPriority = std::make_unique<MockView>();
    auto viewByDate = std::make_unique<MockView>();
    auto storage = std::make_unique<MockStorage>();
    std::weak_ptr<FullTask> weak1;
    weak1 = shared_task1;
    EXPECT_CALL(*viewByPriority, addTask(weak1))
    .Times(1)
    .WillOnce(Return(true));
    EXPECT_CALL(*viewByDate, addTask(weak1))
    .Times(1)
    .WillOnce(Return(true));
    EXPECT_CALL(*storage, addTask(std::move(shared_task1)))
    .Times(1)
    .WillOnce(Return(true));

    time_t now = time(0);
    auto cur = std::make_unique<tm>(*gmtime(&now));
    boost::gregorian::date date1(cur->tm_year+1900, cur->tm_mon + 1, cur->tm_mday);

    TaskService ts(std::move(viewByPriority), std::move(viewByDate), std::move(storage));
    TaskDTO task = TaskDTO::create(date1, "name1", "", TaskPriority::None);

    AddTaskResult outcome  = ts.addTask(task);
    EXPECT_TRUE(outcome.id.has_value());

}

TEST_F(TaskServiceTest, shouldPostponeTask) {
}

TEST_F(TaskServiceTest, shouldGetAllTasksByPriority1) {
    std::vector<std::weak_ptr<FullTask>> weak{shared_task1, shared_task2, shared_task3, shared_task4};
    auto viewByPriority = std::make_unique<MockView>();
    auto viewByDate = std::make_unique<MockView>();
    auto storage = std::make_unique<MockStorage>();

    EXPECT_CALL(*viewByPriority, getAllTasksByPrior)
    .Times(1)
    .WillOnce(Return(weak));

    TaskService ts(std::move(viewByPriority), std::move(viewByDate), std::move(storage));

    auto vec = ts.getAllTasksByPriority();
    EXPECT_EQ(vec.size(), 4);
}

TEST_F(TaskServiceTest, shouldGetAllTasksByPriority2) {
    std::vector<std::weak_ptr<FullTask>> weak;
    auto viewByPriority = std::make_unique<MockView>();
    auto viewByDate = std::make_unique<MockView>();
    auto storage = std::make_unique<MockStorage>();

    EXPECT_CALL(*viewByPriority, getAllTasksByPrior())
    .Times(1)
    .WillOnce(Return(weak));

    TaskService ts(std::move(viewByPriority), std::move(viewByDate), std::move(storage));

    auto vec = ts.getAllTasksByPriority();
    EXPECT_TRUE(vec.empty());
}
