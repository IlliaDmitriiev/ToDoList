//
// Created by Илля on 31.07.2020.
//

#include <gtest/gtest.h>
#include "ViewByDate.h"

class ViewByDateTest : public ::testing::Test {

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

TEST_F(ViewByDateTest, shouldGetFullTasksForToday_1) {
    ViewByDate vbd;
    IDGenerator gen;
    FullTask ft = FullTask::create(gen.generateId(), t1);
    auto sft = std::make_shared<FullTask>(ft);
    vbd.getStorage().addTask(sft);
    auto vec = vbd.getTasksForToday(Date::create(2020, 7, 31));
    ASSERT_TRUE(Task::Compare(vec[0].lock()->getTask(), ft.getTask()));
    ASSERT_EQ(vec[0].lock()->getId().getId(), 0);
}

TEST_F(ViewByDateTest, shouldGetFullTasksForToday_2) {
    ViewByDate vbd;
    IDGenerator gen;
    FullTask ft = FullTask::create(gen.generateId(), t3);
    auto sft = std::make_shared<FullTask>(ft);
    vbd.getStorage().addTask(sft);
    auto vec = vbd.getTasksForToday(Date::create(1500, 2, 26));
    ASSERT_TRUE(Task::Compare(vec[0].lock()->getTask(), ft.getTask()));
    ASSERT_EQ(vec[0].lock()->getId().getId(), 0);
}

TEST_F(ViewByDateTest, shouldGetFullTasksForWeek1) {
    ViewByDate vbd;
    IDGenerator gen;

    FullTask ft1 = FullTask::create(gen.generateId(), t1);
    FullTask ft2 = FullTask::create(gen.generateId(), t2);

    auto sft1 = std::make_shared<FullTask>(ft1);
    auto sft2 = std::make_shared<FullTask>(ft2);

    vbd.getStorage().addTask(sft1);
    vbd.getStorage().addTask(sft2);

    auto vec = vbd.getTasksForWeek(Date::create(2020, 7, 28));

    ASSERT_TRUE(Task::Compare(vec[0].lock()->getTask(), ft1.getTask()));
    ASSERT_EQ(vec[0].lock()->getId().getId(), 0);

    ASSERT_TRUE(Task::Compare(vec[1].lock()->getTask(), ft2.getTask()));
    ASSERT_EQ(vec[1].lock()->getId().getId(), 1);
}

TEST_F(ViewByDateTest, shouldGetFullTasksForWeek2) {
    ViewByDate vbd;
    IDGenerator gen;

    FullTask ft3 = FullTask::create(gen.generateId(), t3);
    FullTask ft4 = FullTask::create(gen.generateId(), t4);
    FullTask ft5 = FullTask::create(gen.generateId(), t5);

    auto sft3 = std::make_shared<FullTask>(ft3);
    auto sft4 = std::make_shared<FullTask>(ft4);
    auto sft5 = std::make_shared<FullTask>(ft5);

    vbd.getStorage().addTask(sft3);
    vbd.getStorage().addTask(sft4);
    vbd.getStorage().addTask(sft5);

    auto vec = vbd.getTasksForWeek(Date::create(1500, 3, 1));

    ASSERT_TRUE(Task::Compare(vec[0].lock()->getTask(), ft3.getTask()));
    ASSERT_EQ(vec[0].lock()->getId().getId(), 0);

    ASSERT_TRUE(Task::Compare(vec[1].lock()->getTask(), ft5.getTask()));
    ASSERT_EQ(vec[1].lock()->getId().getId(), 2);

    ASSERT_TRUE(Task::Compare(vec[2].lock()->getTask(), ft4.getTask()));
    ASSERT_EQ(vec[2].lock()->getId().getId(), 1);
}