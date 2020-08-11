//
// Created by Илля on 03.08.2020.
//

#include <gtest/gtest.h>
#include "logic/ViewByDate.h"

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

class ViewByDateTest : public ::testing::Test {
public:
    ViewByDate storage;
    IDGenerator gen;

    std::shared_ptr<FullTask> sft1;
    std::shared_ptr<FullTask> sft2;
    std::shared_ptr<FullTask> sft3;
    std::shared_ptr<FullTask> sft4;
    std::shared_ptr<FullTask> sft5;

    ViewByDateTest() {
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

TEST_F(ViewByDateTest, shouldAddTask) {

    EXPECT_NO_THROW(storage.addTask(sft1));
    EXPECT_NO_THROW(storage.addTask(sft2));
    EXPECT_NO_THROW(storage.addTask(sft3));
    EXPECT_NO_THROW(storage.addTask(sft4));
    EXPECT_NO_THROW(storage.addTask(sft5));

}

TEST_F(ViewByDateTest, shouldDelete) {
    EXPECT_NO_THROW(storage.addTask(sft1));
    EXPECT_NO_THROW(storage.addTask(sft2));

    EXPECT_TRUE(storage.deleteTask(sft1));
}

TEST_F(ViewByDateTest, shouldNotDelete) {

    EXPECT_FALSE(storage.deleteTask(sft1));
    EXPECT_FALSE(storage.deleteTask(sft5));
}
