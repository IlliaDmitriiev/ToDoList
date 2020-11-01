//
// Created by ilya on 27.09.2020.
//

#include <gtest/gtest.h>
#include "Core/Mock/GeneratorMock.h"
#include "Core/Mock/StorageMock.h"
#include "Core/Mock/ViewMock.h"
#include "Core/model/api/DataHolder.h"

using ::testing::Return;

class DataHolderTest : public ::testing::Test {
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

TEST_F(DataHolderTest, shouldAddTaskSuccessfully) {
    auto viewByPriority = std::make_unique<MockView>();
    auto viewByDate = std::make_unique<MockView>();
    auto storage = std::make_unique<MockStorage>();
    auto generator = std::make_unique<MockGenerator>();

    EXPECT_CALL(*generator, generateId)
            .Times(1)
            .WillOnce(Return(TaskID::create(47)));
    EXPECT_CALL(*viewByPriority, addTask)
            .Times(1)
            .WillOnce(Return(true));
    EXPECT_CALL(*viewByDate, addTask)
            .Times(1)
            .WillOnce(Return(true));
    EXPECT_CALL(*storage, addTask)
            .Times(1)
            .WillOnce(Return(true));

    boost::gregorian::date date1{boost::gregorian::day_clock::local_day()};
    DataHolder data_holder(std::move(generator), std::move(viewByPriority), std::move(viewByDate), std::move(storage));
    ModelTaskDTO task = ModelTaskDTO::create(date1, "name1", "", TaskPriority::None);

    AddTaskResult outcome  = data_holder.addTask(task);
    EXPECT_EQ(outcome.result, ResultType::SUCCESS);
    EXPECT_TRUE(outcome.id.has_value());
    EXPECT_EQ(outcome.id.value().getId(), 47);
}

TEST_F(DataHolderTest, shouldAddTaskUnsuccessfully1) {
    auto viewByPriority = std::make_unique<MockView>();
    auto viewByDate = std::make_unique<MockView>();
    auto storage = std::make_unique<MockStorage>();
    auto generator = std::make_unique<MockGenerator>();

    EXPECT_CALL(*generator, generateId)
            .Times(1)
            .WillOnce(Return(TaskID::create(123)));
    EXPECT_CALL(*viewByPriority, addTask)
            .Times(1)
            .WillOnce(Return(false));
    EXPECT_CALL(*viewByDate, addTask)
            .Times(1)
            .WillOnce(Return(true));

    boost::gregorian::date date{1500, 2, 26};
    DataHolder data_holder(std::move(generator), std::move(viewByPriority), std::move(viewByDate), std::move(storage));

    ModelTaskDTO task = ModelTaskDTO::create(date, "name3", "label3", TaskPriority::Third);
    AddTaskResult outcome  = data_holder.addTask(task);

    EXPECT_EQ(outcome.result, ResultType::FAILURE);
    EXPECT_FALSE(outcome.id.has_value());
}

TEST_F(DataHolderTest, shouldAddTaskUnsuccessfully2) {
    auto viewByPriority = std::make_unique<MockView>();
    auto viewByDate = std::make_unique<MockView>();
    auto storage = std::make_unique<MockStorage>();
    auto generator = std::make_unique<MockGenerator>();

    EXPECT_CALL(*generator, generateId)
            .Times(1)
            .WillOnce(Return(TaskID::create(69)));

    EXPECT_CALL(*viewByDate, addTask)
            .Times(1)
            .WillOnce(Return(false));

    boost::gregorian::date date{boost::gregorian::day_clock::local_day()};
    DataHolder data_holder(std::move(generator), std::move(viewByPriority), std::move(viewByDate), std::move(storage));

    ModelTaskDTO task = ModelTaskDTO::create(date, "name2", "456578y&#&@)(#$?><</*-+fdg", TaskPriority::Second);
    AddTaskResult outcome  = data_holder.addTask(task);

    EXPECT_EQ(outcome.result, ResultType::FAILURE);
    EXPECT_FALSE(outcome.id.has_value());
}

TEST_F(DataHolderTest, shouldNotFindTaskWhileAddSubtask) {
    auto viewByPriority = std::make_unique<MockView>();
    auto viewByDate = std::make_unique<MockView>();
    auto storage = std::make_unique<MockStorage>();
    auto generator = std::make_unique<MockGenerator>();

    EXPECT_CALL(*storage, getTask)
            .Times(1)
            .WillOnce(Return(std::nullopt));

    boost::gregorian::date date{boost::gregorian::day_clock::local_day()};
    DataHolder data_holder(std::move(generator), std::move(viewByPriority), std::move(viewByDate), std::move(storage));

    ModelTaskDTO task = ModelTaskDTO::create(date, "name1", "", TaskPriority::None);
    AddTaskResult outcome  = data_holder.addSubtask(TaskID::create(47), task);

    EXPECT_EQ(outcome.result, ResultType::FAILURE);
    EXPECT_FALSE(outcome.id.has_value());
    EXPECT_EQ(outcome.error_message, "root task with the given id was not found");
}

TEST_F(DataHolderTest, shouldNotAddSubtask) {
    auto viewByPriority = std::make_unique<MockView>();
    auto viewByDate = std::make_unique<MockView>();
    auto storage = std::make_unique<MockStorage>();
    auto generator = std::make_unique<MockGenerator>();

    std::weak_ptr<FullTask> weak2;
    weak2 = shared_task2;

    EXPECT_CALL(*storage, getTask)
            .Times(1)
            .WillOnce(Return(weak2));

    EXPECT_CALL(*generator, generateId)
            .Times(1)
            .WillOnce(Return(TaskID::create(123)));
    EXPECT_CALL(*viewByPriority, addTask)
            .Times(1)
            .WillOnce(Return(false));
    EXPECT_CALL(*viewByDate, addTask)
            .Times(1)
            .WillOnce(Return(true));

    boost::gregorian::date date{1500, 2, 26};

    DataHolder data_holder(std::move(generator), std::move(viewByPriority), std::move(viewByDate), std::move(storage));
    ModelTaskDTO task = ModelTaskDTO::create(date, "name3", "label3", TaskPriority::Third);

    AddTaskResult outcome  = data_holder.addSubtask(TaskID::create(69), task);

    EXPECT_EQ(outcome.result, ResultType::FAILURE);
    EXPECT_FALSE(outcome.id.has_value());
    EXPECT_EQ(outcome.error_message, "subtask creation is failed");
}

TEST_F(DataHolderTest, shouldAddSubtaskSuccessfully) {
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


    EXPECT_CALL(*storage, getTask)
            .Times(2)
            .WillOnce(Return(opt3))
            .WillOnce(Return(opt4));
    EXPECT_CALL(*generator, generateId)
            .Times(1)
            .WillOnce(Return(TaskID::create(8)));
    EXPECT_CALL(*viewByPriority, addTask)
            .Times(1)
            .WillOnce(Return(true));
    EXPECT_CALL(*viewByDate, addTask)
            .Times(1)
            .WillOnce(Return(true));
    EXPECT_CALL(*storage, addTask)
            .Times(1)
            .WillOnce(Return(true));

    boost::gregorian::date date{boost::gregorian::day_clock::local_day()};

    DataHolder data_holder(std::move(generator), std::move(viewByPriority), std::move(viewByDate), std::move(storage));
    ModelTaskDTO task = ModelTaskDTO::create(date, "name4", "", TaskPriority::First);

    AddTaskResult outcome  = data_holder.addSubtask(TaskID::create(123), task);

    EXPECT_EQ(outcome.result, ResultType::SUCCESS);
    EXPECT_TRUE(outcome.id.has_value());
}

TEST_F(DataHolderTest, shouldNotFindTaskWhileDeletingTask) {
    auto viewByPriority = std::make_unique<MockView>();
    auto viewByDate = std::make_unique<MockView>();
    auto storage = std::make_unique<MockStorage>();
    auto generator = std::make_unique<MockGenerator>();

    EXPECT_CALL(*storage, getTask)
            .Times(1)
            .WillOnce(Return(std::nullopt));


    DataHolder data_holder(std::move(generator), std::move(viewByPriority), std::move(viewByDate), std::move(storage));
    RequstTaskResult outcome  = data_holder.deleteTask(TaskID::create(47));

    EXPECT_EQ(outcome.result, ResultType::FAILURE);
    EXPECT_EQ(outcome.error_message, "task not found");
}

TEST_F(DataHolderTest, shouldNotRemoveWhileDeletingTask) {
    auto viewByPriority = std::make_unique<MockView>();
    auto viewByDate = std::make_unique<MockView>();
    auto storage = std::make_unique<MockStorage>();
    auto generator = std::make_unique<MockGenerator>();

    std::weak_ptr<FullTask> weak2;
    weak2 = shared_task2;

    EXPECT_CALL(*storage, getTask)
            .Times(1)
            .WillOnce(Return(weak2));
    EXPECT_CALL(*viewByDate, deleteTask)
            .Times(1)
            .WillOnce(Return(false));

    DataHolder data_holder(std::move(generator), std::move(viewByPriority), std::move(viewByDate), std::move(storage));
    RequstTaskResult outcome  = data_holder.deleteTask(TaskID::create(69));

    EXPECT_EQ(outcome.result, ResultType::FAILURE);
    EXPECT_EQ(outcome.error_message, "deleting is failed");
}

TEST_F(DataHolderTest, shouldNotGetTaskWhileDeletingTask) {
    auto viewByPriority = std::make_unique<MockView>();
    auto viewByDate = std::make_unique<MockView>();
    auto storage = std::make_unique<MockStorage>();
    auto generator = std::make_unique<MockGenerator>();

    std::weak_ptr<FullTask> weak2;
    weak2 = shared_task2;

    EXPECT_CALL(*storage, getTask)
            .Times(1)
            .WillOnce(Return(weak2));
    EXPECT_CALL(*storage, deleteTask)
            .Times(1)
            .WillOnce(Return(false));
    EXPECT_CALL(*storage, deleteSubtaskInParent)
            .Times(1)
            .WillOnce(Return(true));
    EXPECT_CALL(*viewByPriority, deleteTask)
            .Times(1)
            .WillOnce(Return(true));
    EXPECT_CALL(*viewByDate, deleteTask)
            .Times(1)
            .WillOnce(Return(true));

    DataHolder data_holder(std::move(generator), std::move(viewByPriority), std::move(viewByDate), std::move(storage));
    RequstTaskResult outcome  = data_holder.deleteTask(TaskID::create(69));

    EXPECT_EQ(outcome.result, ResultType::FAILURE);
    EXPECT_EQ(outcome.error_message, "can't get task from storage");
}

TEST_F(DataHolderTest, shouldDeleteTaskSuccessfully) {
    auto viewByPriority = std::make_unique<MockView>();
    auto viewByDate = std::make_unique<MockView>();
    auto storage = std::make_unique<MockStorage>();
    auto generator = std::make_unique<MockGenerator>();

    std::weak_ptr<FullTask> weak2;
    weak2 = shared_task2;

    EXPECT_CALL(*storage, getTask)
            .Times(1)
            .WillOnce(Return(weak2));
    EXPECT_CALL(*storage, deleteTask)
            .Times(1)
            .WillOnce(Return(true));
    EXPECT_CALL(*storage, deleteSubtaskInParent)
            .Times(1)
            .WillOnce(Return(true));
    EXPECT_CALL(*viewByPriority, deleteTask)
            .Times(1)
            .WillOnce(Return(true));
    EXPECT_CALL(*viewByDate, deleteTask)
            .Times(1)
            .WillOnce(Return(true));

    DataHolder data_holder(std::move(generator), std::move(viewByPriority), std::move(viewByDate), std::move(storage));
    RequstTaskResult outcome  = data_holder.deleteTask(TaskID::create(69));

    EXPECT_EQ(outcome.result, ResultType::SUCCESS);
}

TEST_F(DataHolderTest, shouldDeleteTaskWithSubtaskSuccessfully) {
    auto viewByPriority = std::make_unique<MockView>();
    auto viewByDate = std::make_unique<MockView>();
    auto storage = std::make_unique<MockStorage>();
    auto generator = std::make_unique<MockGenerator>();

    shared_task2->addSubtask(shared_task3);
    std::weak_ptr<FullTask> weak2 = shared_task2;
    std::weak_ptr<FullTask> weak3 = shared_task3;


    EXPECT_CALL(*storage, getTask)
            .Times(2)
            .WillOnce(Return(weak2))
            .WillOnce(Return(weak3));
    EXPECT_CALL(*storage, deleteTask)
            .Times(2)
            .WillOnce(Return(true))
            .WillOnce(Return(true));
    EXPECT_CALL(*storage, deleteSubtaskInParent)
            .Times(2)
            .WillOnce(Return(true))
            .WillOnce(Return(true));
    EXPECT_CALL(*viewByPriority, deleteTask)
            .Times(2)
            .WillOnce(Return(true))
            .WillOnce(Return(true));
    EXPECT_CALL(*viewByDate, deleteTask)
            .Times(2)
            .WillOnce(Return(true))
            .WillOnce(Return(true));

    DataHolder data_holder(std::move(generator), std::move(viewByPriority), std::move(viewByDate), std::move(storage));
    RequstTaskResult outcome  = data_holder.deleteTask(TaskID::create(69));

    EXPECT_EQ(outcome.result, ResultType::SUCCESS);
}

TEST_F(DataHolderTest, shouldNotFindTaskWhileCompleteTask) {
    auto viewByPriority = std::make_unique<MockView>();
    auto viewByDate = std::make_unique<MockView>();
    auto storage = std::make_unique<MockStorage>();
    auto generator = std::make_unique<MockGenerator>();

    EXPECT_CALL(*storage, getTask)
            .Times(1)
            .WillOnce(Return(std::nullopt));

    DataHolder data_holder(std::move(generator), std::move(viewByPriority), std::move(viewByDate), std::move(storage));
    RequstTaskResult outcome  = data_holder.complete(TaskID::create(69));

    EXPECT_EQ(outcome.result, ResultType::FAILURE);
    EXPECT_EQ(outcome.error_message, "task not found");
}

TEST_F(DataHolderTest, shouldCompleteTask) {
    auto viewByPriority = std::make_unique<MockView>();
    auto viewByDate = std::make_unique<MockView>();
    auto storage = std::make_unique<MockStorage>();
    auto generator = std::make_unique<MockGenerator>();

    std::weak_ptr<FullTask> weak2 = shared_task2;

    EXPECT_CALL(*storage, getTask)
            .Times(1)
            .WillOnce(Return(weak2));

    DataHolder data_holder(std::move(generator), std::move(viewByPriority), std::move(viewByDate), std::move(storage));
    RequstTaskResult outcome  = data_holder.complete(TaskID::create(454896));

    EXPECT_EQ(outcome.result, ResultType::SUCCESS);
}

TEST_F(DataHolderTest, shouldNotEditTask) {
    auto viewByPriority = std::make_unique<MockView>();
    auto viewByDate = std::make_unique<MockView>();
    auto storage = std::make_unique<MockStorage>();
    auto generator = std::make_unique<MockGenerator>();

    EXPECT_CALL(*storage, getTask)
            .Times(1)
            .WillOnce(Return (std::nullopt));

    DataHolder data_holder(std::move(generator), std::move(viewByPriority), std::move(viewByDate), std::move(storage));
    auto new_task =  ModelTaskConvertor::transferToModelTaskDTO(*shared_task4);
    RequstTaskResult outcome  = data_holder.editTask(TaskID::create(454896), new_task);

    EXPECT_EQ(outcome.result, ResultType::FAILURE);
}

TEST_F(DataHolderTest, shouldEditTask) {
    auto viewByPriority = std::make_unique<MockView>();
    auto viewByDate = std::make_unique<MockView>();
    auto storage = std::make_unique<MockStorage>();
    auto generator = std::make_unique<MockGenerator>();

    std::weak_ptr<FullTask> weak2 = shared_task2;

    EXPECT_CALL(*storage, getTask)
            .Times(1)
            .WillOnce(Return(weak2));

    DataHolder data_holder(std::move(generator), std::move(viewByPriority), std::move(viewByDate), std::move(storage));
    auto new_task =  ModelTaskConvertor::transferToModelTaskDTO(*shared_task4);
    RequstTaskResult outcome  = data_holder.editTask(TaskID::create(454896), new_task);

    EXPECT_EQ(outcome.result, ResultType::SUCCESS);
    EXPECT_TRUE(Task::Compare(shared_task2->getTask(), shared_task4->getTask()));
}

TEST_F(DataHolderTest, shouldNotGetPerent1) {
    auto viewByPriority = std::make_unique<MockView>();
    auto viewByDate = std::make_unique<MockView>();
    auto storage = std::make_unique<MockStorage>();
    auto generator = std::make_unique<MockGenerator>();

    EXPECT_CALL(*storage, getTask)
            .Times(1)
            .WillOnce(Return(std::nullopt));

    DataHolder data_holder(std::move(generator), std::move(viewByPriority), std::move(viewByDate), std::move(storage));

    EXPECT_FALSE(data_holder.getParent(TaskID::create(4148)).has_value());
}
TEST_F(DataHolderTest, shouldNotGetPerent2) {
    auto viewByPriority = std::make_unique<MockView>();
    auto viewByDate = std::make_unique<MockView>();
    auto storage = std::make_unique<MockStorage>();
    auto generator = std::make_unique<MockGenerator>();

    std::weak_ptr<FullTask> weak2 = shared_task2;
    EXPECT_CALL(*storage, getTask)
            .Times(1)
            .WillOnce(Return(weak2));

    DataHolder data_holder(std::move(generator), std::move(viewByPriority), std::move(viewByDate), std::move(storage));

    EXPECT_FALSE(data_holder.getParent(weak2.lock()->getId()).has_value());
}

TEST_F(DataHolderTest, shouldGetPerent) {
    auto viewByPriority = std::make_unique<MockView>();
    auto viewByDate = std::make_unique<MockView>();
    auto storage = std::make_unique<MockStorage>();
    auto generator = std::make_unique<MockGenerator>();

    std::weak_ptr<FullTask> weak2 = shared_task2;
    EXPECT_CALL(*storage, getTask)
            .Times(1)
            .WillOnce(Return(weak2));

    DataHolder data_holder(std::move(generator), std::move(viewByPriority), std::move(viewByDate), std::move(storage));

    EXPECT_TRUE(data_holder.getParent(TaskID::create(4148)).has_value());
}


TEST_F(DataHolderTest, shouldGetSubtasks) {
    auto viewByPriority = std::make_unique<MockView>();
    auto viewByDate = std::make_unique<MockView>();
    auto storage = std::make_unique<MockStorage>();
    auto generator = std::make_unique<MockGenerator>();


    EXPECT_CALL(*storage, getTask)
            .Times(7)
            .WillOnce(Return(shared_task1))
            .WillOnce(Return(shared_task2))
            .WillOnce(Return(shared_task1))
            .WillOnce(Return(shared_task3))
            .WillOnce(Return(shared_task1))
            .WillOnce(Return(shared_task2))
            .WillOnce(Return(shared_task3));


    EXPECT_CALL(*generator, generateId)
            .Times(2)
            .WillOnce(Return(TaskID::create(69)))
            .WillOnce(Return(TaskID::create(10000)));
    EXPECT_CALL(*viewByPriority, addTask)
            .Times(2)
            .WillRepeatedly(Return(true));
    EXPECT_CALL(*viewByDate, addTask)
            .Times(2)
            .WillRepeatedly(Return(true));
    EXPECT_CALL(*storage, addTask)
            .Times(2)
            .WillRepeatedly(Return(true));

    DataHolder data_holder(std::move(generator), std::move(viewByPriority), std::move(viewByDate), std::move(storage));
    std::weak_ptr<FullTask> sub1 = shared_task2;
    std::weak_ptr<FullTask> sub2 = shared_task3;

    data_holder.addSubtask(TaskID::create(47), ModelTaskConvertor::transferToModelTaskDTO(*sub1.lock()));
    data_holder.addSubtask(TaskID::create(47), ModelTaskConvertor::transferToModelTaskDTO(*sub2.lock()));

    auto vec = data_holder.getSubtasks(TaskID::create(47));
    EXPECT_EQ(vec.size(), 2);
    EXPECT_EQ(vec[0].getName(), shared_task2->getTask().getName());
    EXPECT_EQ(vec[1].getDate(), shared_task3->getTask().getDate());

}

TEST_F(DataHolderTest, shouldNotGetTask) {
    auto viewByPriority = std::make_unique<MockView>();
    auto viewByDate = std::make_unique<MockView>();
    auto storage = std::make_unique<MockStorage>();
    auto generator = std::make_unique<MockGenerator>();


    EXPECT_CALL(*storage, getTask)
            .Times(1)
            .WillOnce(Return(std::nullopt));


    DataHolder data_holder(std::move(generator), std::move(viewByPriority), std::move(viewByDate), std::move(storage));
    auto opt = data_holder.getTask(TaskID::create(123));
    EXPECT_FALSE(opt.has_value());
}

TEST_F(DataHolderTest, shouldGetAllTasks) {
    auto viewByPriority = std::make_unique<MockView>();
    auto viewByDate = std::make_unique<MockView>();
    auto storage = std::make_unique<MockStorage>();
    auto generator = std::make_unique<MockGenerator>();

    std::vector<std::weak_ptr<FullTask>> vec{shared_task1 , shared_task2};
    EXPECT_CALL(*storage, getAllTasks)
            .Times(1)
            .WillOnce(Return(vec));


    DataHolder data_holder(std::move(generator), std::move(viewByPriority), std::move(viewByDate), std::move(storage));
    auto tasks = data_holder.getAllTasks();
    EXPECT_EQ(tasks.size(), 2);
    EXPECT_TRUE(Task::Compare(ModelTaskConvertor::transferToTask(tasks[0]), shared_task1->getTask()));
    EXPECT_TRUE(Task::Compare(ModelTaskConvertor::transferToTask(tasks[1]), shared_task2->getTask()));
}

TEST_F(DataHolderTest, shouldGetTask) {
    auto viewByPriority = std::make_unique<MockView>();
    auto viewByDate = std::make_unique<MockView>();
    auto storage = std::make_unique<MockStorage>();
    auto generator = std::make_unique<MockGenerator>();

    std::weak_ptr<FullTask> weak4 = shared_task4;
    EXPECT_CALL(*storage, getTask)
            .Times(1)
            .WillOnce(Return(weak4));


    DataHolder data_holder(std::move(generator), std::move(viewByPriority), std::move(viewByDate), std::move(storage));
    auto opt = data_holder.getTask(TaskID::create(123456));
    EXPECT_TRUE(opt.has_value());
}

TEST_F(DataHolderTest, shouldGetAllTasksByPriority1) {
    std::vector<std::weak_ptr<FullTask>> weak{shared_task1, shared_task2, shared_task3, shared_task4};
    auto viewByPriority = std::make_unique<MockView>();
    auto viewByDate = std::make_unique<MockView>();
    auto storage = std::make_unique<MockStorage>();
    auto generator = std::make_unique<MockGenerator>();

    EXPECT_CALL(*viewByPriority, getAllTasksByPrior)
            .Times(1)
            .WillOnce(Return(weak));

    DataHolder data(std::move(generator), std::move(viewByPriority), std::move(viewByDate), std::move(storage));

    auto vec = data.getAllTasksByPriority();
    EXPECT_EQ(vec.size(), 4);
}

TEST_F(DataHolderTest, shouldGetAllTasksByPriority2) {
    std::vector<std::weak_ptr<FullTask>> weak;
    auto viewByPriority = std::make_unique<MockView>();
    auto viewByDate = std::make_unique<MockView>();
    auto storage = std::make_unique<MockStorage>();
    auto generator = std::make_unique<MockGenerator>();

    EXPECT_CALL(*viewByPriority, getAllTasksByPrior)
            .Times(1)
            .WillOnce(Return(weak));

    DataHolder data(std::move(generator), std::move(viewByPriority), std::move(viewByDate), std::move(storage));

    auto vec = data.getAllTasksByPriority();
    EXPECT_TRUE(vec.empty());
}
TEST_F(DataHolderTest, shouldGetTaskForToday) {
    auto viewByPriority = std::make_unique<MockView>();
    auto viewByDate = std::make_unique<MockView>();
    auto storage = std::make_unique<MockStorage>();
    auto generator = std::make_unique<MockGenerator>();

    std::vector< std::weak_ptr<FullTask>>v{shared_task1, shared_task2, shared_task3};

    EXPECT_CALL(*viewByDate, getTasksForToday)
            .Times(1)
            .WillOnce(Return(v));

    boost::gregorian::date date{boost::gregorian::day_clock::local_day()};
    DataHolder data(std::move(generator), std::move(viewByPriority), std::move(viewByDate), std::move(storage));
    auto vec = data.getTasksForToday();
    EXPECT_EQ(vec.size(), v.size());
}

TEST_F(DataHolderTest, shouldGetEmptyVectorOfTaskForToday) {
    auto viewByPriority = std::make_unique<MockView>();
    auto viewByDate = std::make_unique<MockView>();
    auto storage = std::make_unique<MockStorage>();
    auto generator = std::make_unique<MockGenerator>();

    std::vector< std::weak_ptr<FullTask>>v{};

    EXPECT_CALL(*viewByDate, getTasksForToday)
            .Times(1)
            .WillOnce(Return(v));

    boost::gregorian::date date{boost::gregorian::day_clock::local_day()};
    DataHolder data(std::move(generator), std::move(viewByPriority), std::move(viewByDate), std::move(storage));
    auto vec = data.getTasksForToday();
    EXPECT_TRUE(vec.empty());
    EXPECT_EQ(vec.size(), v.size());
}


TEST_F(DataHolderTest, shouldGetTaskForWeek) {
    auto viewByPriority = std::make_unique<MockView>();
    auto viewByDate = std::make_unique<MockView>();
    auto storage = std::make_unique<MockStorage>();
    auto generator = std::make_unique<MockGenerator>();

    std::vector< std::weak_ptr<FullTask>>v{shared_task1, shared_task2, shared_task3};

    EXPECT_CALL(*viewByDate, getTasksForWeek)
            .Times(1)
            .WillOnce(Return(v));

    boost::gregorian::date date{boost::gregorian::day_clock::local_day()};
    DataHolder data(std::move(generator), std::move(viewByPriority), std::move(viewByDate), std::move(storage));
    auto vec = data.getTasksForWeek();
    EXPECT_EQ(vec.size(), v.size());
}

TEST_F(DataHolderTest, shouldGetEmptyVectorOfTaskForWeek) {
    auto viewByPriority = std::make_unique<MockView>();
    auto viewByDate = std::make_unique<MockView>();
    auto storage = std::make_unique<MockStorage>();
    auto generator = std::make_unique<MockGenerator>();

    std::vector< std::weak_ptr<FullTask>>v{};

    EXPECT_CALL(*viewByDate, getTasksForWeek)
            .Times(1)
            .WillOnce(Return(v));

    boost::gregorian::date date{boost::gregorian::day_clock::local_day()};
    DataHolder data(std::move(generator), std::move(viewByPriority), std::move(viewByDate), std::move(storage));
    auto vec = data.getTasksForWeek();
    EXPECT_TRUE(vec.empty());
    EXPECT_EQ(vec.size(), v.size());
}
