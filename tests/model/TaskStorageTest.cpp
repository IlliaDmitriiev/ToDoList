//
// Created by Илля on 03.08.2020.
//

#include <gtest/gtest.h>
#include "model/TaskStorage.h"

const Task t1 = Task::create(
        Date::create(2020, 7, 31),
        "name1",
        "",
        TaskPriority::None);

const Task t2 = Task::create(
        Date::create(2020, 7, 31),
        "name2",
        "456578y&#&@)(#$?><</*-+fdg",
        TaskPriority::Second);


const Task t3 = Task::create(
        Date::create(1500, 2, 26),
        "name3",
        "label3",
        TaskPriority::Third);

const Task t4 = Task::create(
        Date::create(1500, 3, 4),
        "name4",
        "",
        TaskPriority::First);

const Task t5 = Task::create(
        Date::create(1500, 2, 28),
        "",
        "",
        TaskPriority::None);

class StorageForSharedPtrTest : public ::testing::Test {
public:
    TaskStorage storage;
    IDGenerator gen;

    std::shared_ptr<FullTask> sft1;
    std::shared_ptr<FullTask> sft2;
    std::shared_ptr<FullTask> sft3;
    std::shared_ptr<FullTask> sft4;
    std::shared_ptr<FullTask> sft5;

    StorageForSharedPtrTest() {
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

TEST_F(StorageForSharedPtrTest, shoulAddFullTask) {
/*
   storage.addTask(std::move(sft1));
   storage.addTask(std::move(sft2));
   storage.addTask(std::move(sft3));
   storage.addTask(std::move(sft4));
   storage.addTask(std::move(sft5));

   ASSERT_TRUE(Task::Compare(storage.getTask(TaskID::create(0)).lock()->getTask(), t1));
   ASSERT_TRUE(Task::Compare(storage.getTask(TaskID::create(1)).lock()->getTask(), t2));
   ASSERT_TRUE(Task::Compare(storage.getTask(TaskID::create(2)).lock()->getTask(), t3));
   ASSERT_TRUE(Task::Compare(storage.getTask(TaskID::create(3)).lock()->getTask(), t4));
   ASSERT_TRUE(Task::Compare(storage.getTask(TaskID::create(4)).lock()->getTask(), t5));*/
}

TEST_F(StorageForSharedPtrTest, shoulDelete) {
/*
    storage.addTask(std::move(sft1));
    storage.addTask(std::move(sft2));
    storage.addTask(std::move(sft3));
    storage.addTask(std::move(sft4));
    storage.addTask(std::move(sft5));

    storage.deleteTask(TaskID::create(1));
    storage.deleteTask(TaskID::create(3));

    ASSERT_TRUE(Task::Compare(storage.getTask(TaskID::create(0)).lock()->getTask(), t1));
    ASSERT_ANY_THROW(storage.getTask(TaskID::create(1)));
    ASSERT_TRUE(Task::Compare(storage.getTask(TaskID::create(2)).lock()->getTask(), t3));
    ASSERT_ANY_THROW(storage.getTask(TaskID::create(3)));
    ASSERT_TRUE(Task::Compare(storage.getTask(TaskID::create(4)).lock()->getTask(), t5));*/
}
