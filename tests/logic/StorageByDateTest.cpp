//
// Created by Илля on 03.08.2020.
//

#include <gtest/gtest.h>
#include "logic/StorageByDate.h"

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

class StorageByDateTest : public ::testing::Test {
public:
    StorageByDate storage;
    IDGenerator gen;

    std::shared_ptr<FullTask> sft1;
    std::shared_ptr<FullTask> sft2;
    std::shared_ptr<FullTask> sft3;
    std::shared_ptr<FullTask> sft4;
    std::shared_ptr<FullTask> sft5;

    StorageByDateTest() {
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

TEST_F(StorageByDateTest, shouldAddTask) {

    storage.addTask(sft1);
    storage.addTask(sft2);
    storage.addTask(sft3);
    storage.addTask(sft4);
    storage.addTask(sft5);

    auto mp = storage.getMap();

    auto PriorityMap_= mp[Date::create(2020,7,31)].getMap();

    ASSERT_TRUE(Task::Compare(PriorityMap_[0].find(sft1->getId())->second.lock()->getTask(), t1));
    ASSERT_TRUE(Task::Compare(PriorityMap_[2].find(sft2->getId())->second.lock()->getTask(), t2));

}

TEST_F(StorageByDateTest, shouldDelete) {
    storage.addTask(sft1);
    storage.addTask(sft2);

    storage.deleteTask(sft1);

    auto mp = storage.getMap();
    auto PriorityMap_ = mp[Date::create(2020,7,31)].getMap();

    ASSERT_EQ(PriorityMap_[0].find(sft1->getId()), PriorityMap_[0].end());
    ASSERT_TRUE(Task::Compare(PriorityMap_[2].find(sft2->getId())->second.lock()->getTask(), t2));
}
