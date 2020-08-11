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

    ViewByPriorTest() {
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

    storage.addTask(sft1);
    storage.addTask(sft2);
    storage.addTask(sft3);
    storage.addTask(sft4);
    storage.addTask(sft5);

    auto mp = storage.getMap();
    ASSERT_TRUE(Task::Compare(mp[Task::Priority::None][TaskID::create(0)].lock()->getTask(), t1));
    ASSERT_TRUE(Task::Compare(mp[Task::Priority::None][TaskID::create(4)].lock()->getTask(), t5));
    ASSERT_TRUE(Task::Compare(mp[Task::Priority::First][TaskID::create(3)].lock()->getTask(), t4));
    ASSERT_TRUE(Task::Compare(mp[Task::Priority::Second][TaskID::create(1)].lock()->getTask(), t2));
    ASSERT_TRUE(Task::Compare(mp[Task::Priority::Third][TaskID::create(2)].lock()->getTask(), t3));

}

TEST_F(ViewByPriorTest, shouldDeleteTask) {

    storage.addTask(sft1);
    storage.addTask(sft2);
    storage.addTask(sft3);
    storage.addTask(sft4);
    storage.addTask(sft5);

    storage.deleteTask(sft5->getTask().getPrior(), sft5->getId());
    storage.deleteTask(sft3->getTask().getPrior(), sft3->getId());

    auto mp = storage.getMap();

    ASSERT_EQ(mp[Task::Priority::None].find(TaskID::create(4)), mp[Task::Priority::None].end());
    ASSERT_NE(mp[Task::Priority::None].find(TaskID::create(0)), mp[Task::Priority::None].end());
    ASSERT_EQ(mp[Task::Priority::Third].find(TaskID::create(2)), mp[Task::Priority::Third].end());
}

TEST_F(ViewByPriorTest, shouldGetAllTasksByPriority) {

    storage.addTask(sft4);
    storage.addTask(sft5);

    auto vec = storage.getAllTasks();

    ASSERT_EQ(vec.size(), 2);
    ASSERT_TRUE(Task::Compare(vec[0].lock()->getTask(), t4));
    ASSERT_TRUE(Task::Compare(vec[1].lock()->getTask(), t5));


}

