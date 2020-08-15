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
        FullTask task1 = FullTask::create(TaskID::create(47), t1);
        FullTask task2 = FullTask::create(TaskID::create(69), t2);
        FullTask task3 = FullTask::create(TaskID::create(123), t3);
        FullTask task4 = FullTask::create(TaskID::create(8), t4);

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

class MockGenerator : public IDGeneratorInterface {

public:
    MOCK_METHOD(TaskID, generateId, (), (override));
};

bool operator == (const TaskID &id1, const TaskID &id2){
    return id1.getId() == id2.getId();
}

bool operator == (const std::weak_ptr<FullTask> &task1, const std::weak_ptr<FullTask> &task2){
    return task1.lock()->getId()== task2.lock()->getId();
}

bool operator == (const std::shared_ptr<FullTask> &task1, const std::shared_ptr<FullTask> &task2){
    return task1->getId()== task2->getId();
}

TEST_F(TaskServiceTest, shouldAddTaskSuccessfully) {
    auto viewByPriority = std::make_unique<MockView>();
    auto viewByDate = std::make_unique<MockView>();
    auto storage = std::make_unique<MockStorage>();
    auto generator = std::make_unique<MockGenerator>();
    std::weak_ptr<FullTask> weak1;
    weak1 = shared_task1;
    EXPECT_CALL(*generator, generateId())
    .Times(1)
    .WillOnce(Return(TaskID::create(47)));
    EXPECT_CALL(*viewByPriority, addTask(weak1))
    .Times(1)
    .WillOnce(Return(true));
    EXPECT_CALL(*viewByDate, addTask(weak1))
    .Times(1)
    .WillOnce(Return(true));
    EXPECT_CALL(*storage, addTask(std::move(shared_task1)))
    .Times(1)
    .WillOnce(Return(true));

    boost::gregorian::date date1{boost::gregorian::day_clock::local_day()};
    TaskService ts(std::move(generator), std::move(viewByPriority), std::move(viewByDate), std::move(storage));
    TaskDTO task = TaskDTO::create(date1, "name1", "", TaskPriority::None);

    AddTaskResult outcome  = ts.addTask(task);
    EXPECT_EQ(outcome.result, ResultType::SUCCESS);
    EXPECT_TRUE(outcome.id.has_value());
    EXPECT_EQ(outcome.id.value().getId(), 47);
}

TEST_F(TaskServiceTest, shouldAddTaskUnsuccessfully1) {
    auto viewByPriority = std::make_unique<MockView>();
    auto viewByDate = std::make_unique<MockView>();
    auto storage = std::make_unique<MockStorage>();
    auto generator = std::make_unique<MockGenerator>();
    std::weak_ptr<FullTask> weak1;
    weak1 = shared_task3;
    EXPECT_CALL(*generator, generateId())
            .Times(1)
            .WillOnce(Return(TaskID::create(123)));
    EXPECT_CALL(*viewByPriority, addTask(weak1))
            .Times(1)
            .WillOnce(Return(false));
    EXPECT_CALL(*viewByDate, addTask(weak1))
            .Times(1)
            .WillOnce(Return(true));

    boost::gregorian::date date{1500, 2, 26};

    TaskService ts(std::move(generator), std::move(viewByPriority), std::move(viewByDate), std::move(storage));
    TaskDTO task = TaskDTO::create(date, "name3", "label3", TaskPriority::Third);

    AddTaskResult outcome  = ts.addTask(task);
    EXPECT_EQ(outcome.result, ResultType::FAILURE);
    EXPECT_FALSE(outcome.id.has_value());
}

TEST_F(TaskServiceTest, shouldAddTaskUnsuccessfully2) {
    auto viewByPriority = std::make_unique<MockView>();
    auto viewByDate = std::make_unique<MockView>();
    auto storage = std::make_unique<MockStorage>();
    auto generator = std::make_unique<MockGenerator>();

    std::weak_ptr<FullTask> weak1;
    weak1 = shared_task2;

    EXPECT_CALL(*generator, generateId())
            .Times(1)
            .WillOnce(Return(TaskID::create(69)));

    EXPECT_CALL(*viewByDate, addTask(weak1))
            .Times(1)
            .WillOnce(Return(false));

    boost::gregorian::date date{boost::gregorian::day_clock::local_day()};

    TaskService ts(std::move(generator), std::move(viewByPriority), std::move(viewByDate), std::move(storage));
    TaskDTO task = TaskDTO::create(date, "name2", "456578y&#&@)(#$?><</*-+fdg", TaskPriority::Second);
    AddTaskResult outcome  = ts.addTask(task);

    EXPECT_EQ(outcome.result, ResultType::FAILURE);
    EXPECT_FALSE(outcome.id.has_value());
}

TEST_F(TaskServiceTest, shouldNotFindTaskWhileAddSubtask) {
    auto viewByPriority = std::make_unique<MockView>();
    auto viewByDate = std::make_unique<MockView>();
    auto storage = std::make_unique<MockStorage>();
    auto generator = std::make_unique<MockGenerator>();

    EXPECT_CALL(*storage, getTask(TaskID::create(47)))
            .Times(1)
            .WillOnce(Return(std::nullopt));

    boost::gregorian::date date{boost::gregorian::day_clock::local_day()};
    TaskService ts(std::move(generator), std::move(viewByPriority), std::move(viewByDate), std::move(storage));

    TaskDTO task = TaskDTO::create(date, "name1", "", TaskPriority::None);
    AddTaskResult outcome  = ts.addSubtask(TaskID::create(47), task);

    EXPECT_EQ(outcome.result, ResultType::FAILURE);
    EXPECT_FALSE(outcome.id.has_value());
    EXPECT_EQ(outcome.error_message, "task not found");
}

TEST_F(TaskServiceTest, shouldNotAddSubtask) {
    auto viewByPriority = std::make_unique<MockView>();
    auto viewByDate = std::make_unique<MockView>();
    auto storage = std::make_unique<MockStorage>();
    auto generator = std::make_unique<MockGenerator>();

    std::weak_ptr<FullTask> weak2;
    std::weak_ptr<FullTask> weak3;
    weak3 = shared_task3;
    weak2 = shared_task2;

    EXPECT_CALL(*storage, getTask(TaskID::create(69)))
            .Times(1)
            .WillOnce(Return(weak2));

    EXPECT_CALL(*generator, generateId())
            .Times(1)
            .WillOnce(Return(TaskID::create(123)));
    EXPECT_CALL(*viewByPriority, addTask(weak3))
            .Times(1)
            .WillOnce(Return(false));
    EXPECT_CALL(*viewByDate, addTask(weak3))
            .Times(1)
            .WillOnce(Return(true));

    boost::gregorian::date date{1500, 2, 26};

    TaskService ts(std::move(generator), std::move(viewByPriority), std::move(viewByDate), std::move(storage));
    TaskDTO task = TaskDTO::create(date, "name3", "label3", TaskPriority::Third);

    AddTaskResult outcome  = ts.addSubtask(TaskID::create(69), task);

    EXPECT_EQ(outcome.result, ResultType::FAILURE);
    EXPECT_FALSE(outcome.id.has_value());
    EXPECT_EQ(outcome.error_message, "subtask creation is failed");
}

TEST_F(TaskServiceTest, shouldAddSubtaskSuccessfully) {
    auto viewByPriority = std::make_unique<MockView>();
    auto viewByDate = std::make_unique<MockView>();
    auto storage = std::make_unique<MockStorage>();
    auto generator = std::make_unique<MockGenerator>();

    std::weak_ptr<FullTask> weak3;
    std::weak_ptr<FullTask> weak4;
    weak3 = shared_task3;
    weak4 = shared_task4;
    std::optional<std::weak_ptr<FullTask>> opt3= weak3;
    std::optional<std::weak_ptr<FullTask>> opt4 = weak4;


    EXPECT_CALL(*storage, getTask(TaskID::create(123)))
            .Times(1)
            .WillOnce(Return(opt3));
    EXPECT_CALL(*storage, getTask(TaskID::create(8)))
            .Times(1)
            .WillOnce(Return(opt4));

    EXPECT_CALL(*generator, generateId())
            .Times(1)
            .WillOnce(Return(TaskID::create(8)));
    EXPECT_CALL(*viewByPriority, addTask(weak4))
            .Times(1)
            .WillOnce(Return(true));
    EXPECT_CALL(*viewByDate, addTask(weak4))
            .Times(1)
            .WillOnce(Return(true));
    EXPECT_CALL(*storage, addTask(std::move(shared_task4)))
            .Times(1)
            .WillOnce(Return(true));

    boost::gregorian::date date{boost::gregorian::day_clock::local_day()};

    TaskService ts(std::move(generator), std::move(viewByPriority), std::move(viewByDate), std::move(storage));
    TaskDTO task = TaskDTO::create(date, "name4", "", TaskPriority::First);

    AddTaskResult outcome  = ts.addSubtask(TaskID::create(123), task);

    EXPECT_EQ(outcome.result, ResultType::SUCCESS);
    EXPECT_TRUE(outcome.id.has_value());
}

TEST_F(TaskServiceTest, shouldGetAllTasksByPriority1) {
    std::vector<std::weak_ptr<FullTask>> weak{shared_task1, shared_task2, shared_task3, shared_task4};
    auto viewByPriority = std::make_unique<MockView>();
    auto viewByDate = std::make_unique<MockView>();
    auto storage = std::make_unique<MockStorage>();
    auto generator = std::make_unique<MockGenerator>();

    EXPECT_CALL(*viewByPriority, getAllTasksByPrior)
    .Times(1)
    .WillOnce(Return(weak));

    TaskService ts(std::move(generator), std::move(viewByPriority), std::move(viewByDate), std::move(storage));

    auto vec = ts.getAllTasksByPriority();
    EXPECT_EQ(vec.size(), 4);
}

TEST_F(TaskServiceTest, shouldGetAllTasksByPriority2) {
    std::vector<std::weak_ptr<FullTask>> weak;
    auto viewByPriority = std::make_unique<MockView>();
    auto viewByDate = std::make_unique<MockView>();
    auto storage = std::make_unique<MockStorage>();
    auto generator = std::make_unique<MockGenerator>();

    EXPECT_CALL(*viewByPriority, getAllTasksByPrior())
    .Times(1)
    .WillOnce(Return(weak));

    TaskService ts(std::move(generator), std::move(viewByPriority), std::move(viewByDate), std::move(storage));

    auto vec = ts.getAllTasksByPriority();
    EXPECT_TRUE(vec.empty());
}
