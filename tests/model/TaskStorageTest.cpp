//
// Created by Илля on 03.08.2020.
//

#include <gtest/gtest.h>
#include "model/TaskStorage.h"

const Task t1 = Task::create(
        boost::gregorian::date(2020, 7, 31),
        "name1",
        "",
        TaskPriority::None);

const Task t2 = Task::create(
        boost::gregorian::date(2020, 7, 31),
        "name2",
        "456578y&#&@)(#$?><</*-+fdg",
        TaskPriority::Second);


const Task t3 = Task::create(
        boost::gregorian::date(1500, 2, 26),
        "name3",
        "label3",
        TaskPriority::Third);

const Task t4 = Task::create(
        boost::gregorian::date(1500, 3, 4),
        "name4",
        "",
        TaskPriority::First);

const Task t5 = Task::create(
        boost::gregorian::date(1500, 2, 28),
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

    storage.addTask(std::move(sft1));
    storage.addTask(std::move(sft2));

    EXPECT_TRUE(storage.getTask(TaskID::create(0)).has_value());
    EXPECT_TRUE(storage.getTask(TaskID::create(1)).has_value());
}

TEST_F(StorageForSharedPtrTest, shouldGetTaskSuccessfully) {
    storage.addTask(std::move(sft3));
    storage.addTask(std::move(sft4));

    EXPECT_TRUE(storage.getTask(TaskID::create(2)).has_value());
    EXPECT_TRUE(storage.getTask(TaskID::create(3)).has_value());

}

TEST_F(StorageForSharedPtrTest, shouldGetTaskUnsuccessfully) {
    EXPECT_FALSE(storage.getTask(TaskID::create(2)).has_value());
    storage.addTask(std::move(sft3));
    storage.addTask(std::move(sft4));

    EXPECT_FALSE(storage.getTask(TaskID::create(0)).has_value());
    EXPECT_FALSE(storage.getTask(TaskID::create(1)).has_value());

}

TEST_F(StorageForSharedPtrTest, shouldNotFindParentTaskWhileDeleteSubtaskInParent) {

    storage.addTask(std::move(sft1));
    storage.addTask(std::move(sft2));

    EXPECT_FALSE(storage.deleteSubtaskInParent(TaskID::create(47), TaskID::create(47)));
}

TEST_F(StorageForSharedPtrTest, shouldNotFindSubtaskWhileDeleteSubtaskInParent) {

    storage.addTask(std::move(sft1));
    storage.addTask(std::move(sft2));

    EXPECT_FALSE(storage.deleteSubtaskInParent(TaskID::create(0), TaskID::create(47)));
}

TEST_F(StorageForSharedPtrTest, shouldDeleteSubtaskInParent) {
    sft1->addSubtask(sft2);
    storage.addTask(std::move(sft1));
    storage.addTask(std::move(sft2));

    EXPECT_TRUE(storage.deleteSubtaskInParent(TaskID::create(0), TaskID::create(1)));
}

TEST_F(StorageForSharedPtrTest, shouldDeleteTask) {

    storage.addTask(std::move(sft1));
    storage.addTask(std::move(sft2));

    EXPECT_TRUE(storage.deleteTask(TaskID::create(1)));
}

TEST_F(StorageForSharedPtrTest, shouldNotDeleteTask) {

    storage.addTask(std::move(sft1));
    storage.addTask(std::move(sft2));

    EXPECT_FALSE(storage.deleteTask(TaskID::create(4548)));
}

