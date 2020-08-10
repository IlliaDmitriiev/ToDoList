//
// Created by Илля on 01.08.2020.
//

#include <gtest/gtest.h>
#include "logic/ViewByPriority.h"

class ViewByPriorityTest : public ::testing::Test {

};

const Task t1 = Task::create(
        Date::create(2020, 7, 31),
        "name1",
        "",
        Task::Priority::None);

const Task t2 = Task::create(
        Date::create(2020, 8, 2),
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

TEST_F(ViewByPriorityTest, shouldGetAllFullTasksByPriority) {
    ViewByPriority vbp;
    IDGenerator gen;

    FullTask ft1 = FullTask::create(gen.generateId(), t1);
    FullTask ft2 = FullTask::create(gen.generateId(), t2);
    FullTask ft3 = FullTask::create(gen.generateId(), t3);
    FullTask ft4 = FullTask::create(gen.generateId(), t4);
    FullTask ft5 = FullTask::create(gen.generateId(), t5);

    auto sft1 = std::make_shared<FullTask>(ft1);
    auto sft2 = std::make_shared<FullTask>(ft2);
    auto sft3 = std::make_shared<FullTask>(ft3);
    auto sft4 = std::make_shared<FullTask>(ft4);
    auto sft5 = std::make_shared<FullTask>(ft5);

    vbp.getStorage().addTask(sft1);
    vbp.getStorage().addTask(sft2);
    vbp.getStorage().addTask(sft3);
    vbp.getStorage().addTask(sft4);
    vbp.getStorage().addTask(sft5);

    auto vec = vbp.getAllTasks();

    ASSERT_TRUE(Task::Compare(vec[0].lock()->getTask(), ft4.getTask()));
    ASSERT_EQ(vec[0].lock()->getId().getId(), 3);
    ASSERT_TRUE(Task::Compare(vec[1].lock()->getTask(), ft2.getTask()));
    ASSERT_EQ(vec[1].lock()->getId().getId(), 1);
    ASSERT_TRUE(Task::Compare(vec[2].lock()->getTask(), ft3.getTask()));
    ASSERT_EQ(vec[2].lock()->getId().getId(), 2);
    ASSERT_TRUE(Task::Compare(vec[3].lock()->getTask(), ft1.getTask()));
    ASSERT_EQ(vec[3].lock()->getId().getId(), 0);
    ASSERT_TRUE(Task::Compare(vec[4].lock()->getTask(), ft5.getTask()));
    ASSERT_EQ(vec[4].lock()->getId().getId(), 4);

}

