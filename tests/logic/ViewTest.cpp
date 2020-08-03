//
// Created by Илля on 04.08.2020.
//


#include <gtest/gtest.h>
#include "View.h"

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
        Date::create(1500, 2, 28),
        "",
        "",
        Task::Priority::None);

class ViewTest : public ::testing::Test {
public:
    IDGenerator gen;

    std::shared_ptr<FullTask> sft1;
    std::shared_ptr<FullTask> sft2;
    std::shared_ptr<FullTask> sft3;
    std::shared_ptr<FullTask> sft4;

    ViewTest() {
        FullTask ft1 = FullTask::create(gen.generateId(), t1);
        FullTask ft2 = FullTask::create(gen.generateId(), t2);
        FullTask ft3 = FullTask::create(gen.generateId(), t3);
        FullTask ft4 = FullTask::create(gen.generateId(), t4);

        sft1 = std::make_shared<FullTask>(ft1);
        sft2 = std::make_shared<FullTask>(ft2);
        sft3 = std::make_shared<FullTask>(ft3);
        sft4 = std::make_shared<FullTask>(ft4);
    }

};

TEST_F(ViewTest, shouldGetAllTasksByPrior) {
    View view;
    view.getViewByP().getStorage().putTaskInRightPlace(sft1);
    view.getViewByP().getStorage().putTaskInRightPlace(sft2);
    view.getViewByP().getStorage().putTaskInRightPlace(sft3);
    view.getViewByP().getStorage().putTaskInRightPlace(sft4);

    auto vec = view.getAllTasksByPrior();
    ASSERT_EQ(vec.size(), 4);
    ASSERT_TRUE(Task::Compare(vec[0].lock()->getTask(), t2));
    ASSERT_TRUE(Task::Compare(vec[1].lock()->getTask(), t3));
    ASSERT_TRUE(Task::Compare(vec[2].lock()->getTask(), t1));
    ASSERT_TRUE(Task::Compare(vec[3].lock()->getTask(), t4));
}
