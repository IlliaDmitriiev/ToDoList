//
// Created by Илля on 01.08.2020.
//

#include <gtest/gtest.h>
#include "logic/ViewByPriority.h"

const Task t1 = Task::create(
        Date::create(2020, 7, 31),
        "name1",
        "",
        Task::Priority::None);

const Task t2 = Task::create(
        Date::create(2020, 7, 31),
        "name2",
        "456578y&#&@)(#$?><</*-+fdg",
        Task::Priority::Second);


const Task t3 = Task::create(
        Date::create(1500, 2, 26),
        "name3",
        "label3",
        Task::Priority::Third);

const Task t4 = Task::create(
        Date::create(1500, 3, 4),
        "name4",
        "",
        Task::Priority::First);

const Task t5 = Task::create(
        Date::create(1500, 2, 28),
        "",
        "",
        Task::Priority::None);

class ViewByPriorTest : public ::testing::Test {
public:
    ViewByPriority storage;
    IDGenerator gen;

    std::shared_ptr<FullTask> sft1;
    std::shared_ptr<FullTask> sft2;
    std::shared_ptr<FullTask> sft3;
    std::shared_ptr<FullTask> sft4;
    std::shared_ptr<FullTask> sft5;

    void SetUp() override {
        FullTask ft1 = FullTask::create(gen.generateId(), t1);
        FullTask ft2 = FullTask::create(gen.generateId(), t2);
        FullTask ft3 = FullTask::create(gen.generateId(), t3);
        FullTask ft4 = FullTask::create(gen.generateId(), t4);
        FullTask ft5 = FullTask::create(gen.generateId(), t5);

        sft1 = std::make_shared<FullTask>(ft1);
        sft2 = std::make_shared<FullTask>(ft2);
        sft3 = std::make_shared<FullTask>(ft3);
        sft4 = std::make_shared<FullTask>(ft4);
        sft5 = std::make_shared<FullTask>(ft5);
    }

};

TEST_F(ViewByPriorTest, shouldAddTask) {

    EXPECT_NO_THROW(storage.addTask(sft1));
    EXPECT_NO_THROW(storage.addTask(sft2));
    EXPECT_NO_THROW(storage.addTask(sft3));
    EXPECT_NO_THROW(storage.addTask(sft4));
    EXPECT_NO_THROW(storage.addTask(sft5));
}

TEST_F(ViewByPriorTest, shouldDeleteTask) {

    EXPECT_NO_THROW(storage.addTask(sft1));
    EXPECT_NO_THROW(storage.addTask(sft2));
    EXPECT_NO_THROW(storage.addTask(sft3));
    EXPECT_NO_THROW(storage.addTask(sft4));
    EXPECT_NO_THROW(storage.addTask(sft5));

    EXPECT_TRUE(storage.deleteTask(sft5));
    EXPECT_TRUE(storage.deleteTask(sft3));
}

TEST_F(ViewByPriorTest, shouldGetAllTasksByPriority) {

    storage.addTask(sft4);
    storage.addTask(sft5);

    auto vec = storage.getAllTasksByPrior();

    EXPECT_EQ(vec.size(), 2);
    EXPECT_TRUE(Task::Compare(vec[0].lock()->getTask(), t4));
    EXPECT_TRUE(Task::Compare(vec[1].lock()->getTask(), t5));
}

TEST_F(ViewByPriorTest, shouldDeleteNonExistentTask) {
    EXPECT_FALSE(storage.deleteTask(sft4));
}

TEST_F(ViewByPriorTest, shouldGetEmptyVector) {
    EXPECT_TRUE(storage.getAllTasksByPrior().empty());
}

TEST_F(ViewByPriorTest, shouldGenerateEmptyVectorOfTasksForToday) {
    time_t now = time(0);
    auto cur = std::make_unique<tm>(*gmtime(&now));
    Date date = Date::create(cur->tm_year+1900, cur->tm_mon + 1, cur->tm_mday);

    EXPECT_TRUE(storage.getTasksForToday(date).empty());
}

TEST_F(ViewByPriorTest, shouldGenerateEmptyVectorOfTasksForWeek) {
    time_t now = time(0);
    auto cur = std::make_unique<tm>(*gmtime(&now));
    Date date = Date::create(cur->tm_year+1900, cur->tm_mon + 1, cur->tm_mday);

    EXPECT_TRUE(storage.getTasksForWeek(date).empty());
}
