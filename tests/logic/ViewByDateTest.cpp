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

TEST_F(ViewByDateTest, shouldGetFullTasksForToday) {
    ViewByDate vbd;
    IDGenerator gen;
    FullTask ft = FullTask::create(gen, t1);
    auto sft = std::make_shared<FullTask>(ft);
    vbd.getStorage().addTask(sft);
    auto vec = vbd.getTasksForToday(Date::create(2020, 7, 31));
    ASSERT_EQ(vec[0].lock()->getTask().getDate().getYear(), 2020);
    ASSERT_EQ(vec[0].lock()->getTask().getDate().getMounth(), 7);
    ASSERT_EQ(vec[0].lock()->getTask().getDate().getDay(), 31);
    ASSERT_EQ(vec[0].lock()->getTask().getName(), "name1");
    ASSERT_EQ(vec[0].lock()->getTask().getLabel(), "");
    ASSERT_EQ(vec[0].lock()->getTask().getPrior(), Task::Priority::None);
}

TEST_F(ViewByDateTest, shouldGetFullTasksForWeek1) {
    ViewByDate vbd;
    IDGenerator gen;

    FullTask ft1 = FullTask::create(gen, t1);
    FullTask ft2 = FullTask::create(gen, t2);

    auto sft1 = std::make_shared<FullTask>(ft1);
    auto sft2 = std::make_shared<FullTask>(ft2);

    vbd.getStorage().addTask(sft1);
    vbd.getStorage().addTask(sft2);

    auto vec = vbd.getTasksForWeek(Date::create(2020, 7, 28));
    ASSERT_EQ(vec[0].lock()->getTask().getDate().getYear(), 2020);
    ASSERT_EQ(vec[0].lock()->getTask().getDate().getMounth(), 7);
    ASSERT_EQ(vec[0].lock()->getTask().getDate().getDay(), 31);
    ASSERT_EQ(vec[0].lock()->getTask().getName(), "name1");
    ASSERT_EQ(vec[0].lock()->getTask().getLabel(), "");
    ASSERT_EQ(vec[0].lock()->getTask().getPrior(), Task::Priority::None);

    ASSERT_EQ(vec[1].lock()->getTask().getDate().getYear(), 2020);
    ASSERT_EQ(vec[1].lock()->getTask().getDate().getMounth(), 8);
    ASSERT_EQ(vec[1].lock()->getTask().getDate().getDay(), 2);
    ASSERT_EQ(vec[1].lock()->getTask().getName(), "name2");
    ASSERT_EQ(vec[1].lock()->getTask().getLabel(), "456578y&#&@)(#$?><</*-+fdg");
    ASSERT_EQ(vec[1].lock()->getTask().getPrior(), Task::Priority::Second);
}

TEST_F(ViewByDateTest, shouldGetFullTasksForWeek2) {
    ViewByDate vbd;
    IDGenerator gen;

    FullTask ft3 = FullTask::create(gen, t3);
    FullTask ft4 = FullTask::create(gen, t4);
    FullTask ft5 = FullTask::create(gen, t5);

    auto sft3 = std::make_shared<FullTask>(ft3);
    auto sft4 = std::make_shared<FullTask>(ft4);
    auto sft5 = std::make_shared<FullTask>(ft5);

    vbd.getStorage().addTask(sft3);
    vbd.getStorage().addTask(sft4);
    vbd.getStorage().addTask(sft5);

    auto vec = vbd.getTasksForWeek(Date::create(1500, 3, 1));

    ASSERT_EQ(vec[0].lock()->getTask().getDate().getYear(), 1500);
    ASSERT_EQ(vec[0].lock()->getTask().getDate().getMounth(), 2);
    ASSERT_EQ(vec[0].lock()->getTask().getDate().getDay(), 26);
    ASSERT_EQ(vec[0].lock()->getTask().getName(), "name3");
    ASSERT_EQ(vec[0].lock()->getTask().getLabel(), "label3");
    ASSERT_EQ(vec[0].lock()->getTask().getPrior(), Task::Priority::Third);

    ASSERT_EQ(vec[1].lock()->getTask().getDate().getYear(), 1500);
    ASSERT_EQ(vec[1].lock()->getTask().getDate().getMounth(), 2);
    ASSERT_EQ(vec[1].lock()->getTask().getDate().getDay(), 28);
    ASSERT_EQ(vec[1].lock()->getTask().getName(), "");
    ASSERT_EQ(vec[1].lock()->getTask().getLabel(), "");
    ASSERT_EQ(vec[1].lock()->getTask().getPrior(), Task::Priority::None);

    ASSERT_EQ(vec[2].lock()->getTask().getDate().getYear(), 1500);
    ASSERT_EQ(vec[2].lock()->getTask().getDate().getMounth(), 3);
    ASSERT_EQ(vec[2].lock()->getTask().getDate().getDay(), 4);
    ASSERT_EQ(vec[2].lock()->getTask().getName(), "name4");
    ASSERT_EQ(vec[2].lock()->getTask().getLabel(), "");
    ASSERT_EQ(vec[2].lock()->getTask().getPrior(), Task::Priority::First);
}