//
// Created by Илля on 01.08.2020.
//

#include <gtest/gtest.h>
#include "ViewByPriority.h"

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

TEST_F(ViewByPriorityTest, shouldGetAllFullTasks) {
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

    vbp.getStorage().putTaskInRightPlace(sft1);
    vbp.getStorage().putTaskInRightPlace(sft2);
    vbp.getStorage().putTaskInRightPlace(sft3);
    vbp.getStorage().putTaskInRightPlace(sft4);
    vbp.getStorage().putTaskInRightPlace(sft5);

    auto vec = vbp.getAllTasks();
    ASSERT_EQ(vec[0].lock()->getTask().getDate().getYear(), 1500);
    ASSERT_EQ(vec[0].lock()->getTask().getDate().getMounth(), 3);
    ASSERT_EQ(vec[0].lock()->getTask().getDate().getDay(), 4);
    ASSERT_EQ(vec[0].lock()->getTask().getName(), "name4");
    ASSERT_EQ(vec[0].lock()->getTask().getLabel(), "");
    ASSERT_EQ(vec[0].lock()->getTask().getPrior(), Task::Priority::First);

    ASSERT_EQ(vec[1].lock()->getTask().getDate().getYear(), 2020);
    ASSERT_EQ(vec[1].lock()->getTask().getDate().getMounth(), 8);
    ASSERT_EQ(vec[1].lock()->getTask().getDate().getDay(), 2);
    ASSERT_EQ(vec[1].lock()->getTask().getName(), "name2");
    ASSERT_EQ(vec[1].lock()->getTask().getLabel(), "456578y&#&@)(#$?><</*-+fdg");
    ASSERT_EQ(vec[1].lock()->getTask().getPrior(), Task::Priority::Second);

    ASSERT_EQ(vec[2].lock()->getTask().getDate().getYear(), 1500);
    ASSERT_EQ(vec[2].lock()->getTask().getDate().getMounth(), 2);
    ASSERT_EQ(vec[2].lock()->getTask().getDate().getDay(), 26);
    ASSERT_EQ(vec[2].lock()->getTask().getName(), "name3");
    ASSERT_EQ(vec[2].lock()->getTask().getLabel(), "label3");
    ASSERT_EQ(vec[2].lock()->getTask().getPrior(), Task::Priority::Third);

    ASSERT_EQ(vec[3].lock()->getTask().getDate().getYear(), 2020);
    ASSERT_EQ(vec[3].lock()->getTask().getDate().getMounth(), 7);
    ASSERT_EQ(vec[3].lock()->getTask().getDate().getDay(), 31);
    ASSERT_EQ(vec[3].lock()->getTask().getName(), "name1");
    ASSERT_EQ(vec[3].lock()->getTask().getLabel(), "");
    ASSERT_EQ(vec[3].lock()->getTask().getPrior(), Task::Priority::None);

    ASSERT_EQ(vec[4].lock()->getTask().getDate().getYear(), 1500);
    ASSERT_EQ(vec[4].lock()->getTask().getDate().getMounth(), 2);
    ASSERT_EQ(vec[4].lock()->getTask().getDate().getDay(), 28);
    ASSERT_EQ(vec[4].lock()->getTask().getName(), "");
    ASSERT_EQ(vec[4].lock()->getTask().getLabel(), "");
    ASSERT_EQ(vec[4].lock()->getTask().getPrior(), Task::Priority::None);
}

