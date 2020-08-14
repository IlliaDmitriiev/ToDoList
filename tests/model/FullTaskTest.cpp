//
// Created by illia.dmitriiev on 8/4/2020.
//

#include <gtest/gtest.h>
#include "model/FullTask.h"

class FullTaskTest : public ::testing::Test {

};

TEST_F(FullTaskTest, shouldCreate) {
    IDGenerator gen;
    Task t = Task::create(
            Date::create(2020, 7, 31),
            "name1",
            "",
            TaskPriority::None);
    FullTask ft = FullTask::create(gen.generateId(), t);
    EXPECT_TRUE(Task::Compare(t, ft.getTask()));
}

TEST_F(FullTaskTest, shouldGetTask) {
    Task t = Task::create(
            Date::create(2020, 7, 31),
            "",
            "",
            TaskPriority::First);
    FullTask ft = FullTask::create(TaskID::create(1255), t);
    Task task = ft.getTask();
    EXPECT_TRUE(Task::Compare(t, task));
}

TEST_F(FullTaskTest, shouldGetId) {
    IDGenerator gen;
    Task t = Task::create(
            Date::create(2020, 7, 31),
            "name1",
            "",
            TaskPriority::None);
    FullTask ft = FullTask::create(gen.generateId(), t);
    EXPECT_EQ(ft.getId().getId(),0);
}

TEST_F(FullTaskTest, shouldBeCompleted) {
    Task t = Task::create(
            Date::create(20, 8, 1),
            "",
            "",
            TaskPriority::Second);
    FullTask ft = FullTask::create(TaskID::create(8), t);
    ft.complete();
    EXPECT_TRUE(ft.isComplete());
}

TEST_F(FullTaskTest, shouldCreateParent) {
    IDGenerator gen;
    Task t1 = Task::create(
            Date::create(2020, 7, 31),
            "name1",
            "",
            TaskPriority::None);
    Task t2 = Task::create(
            Date::create(2485, 3, 5),
            "name2",
            "label",
            TaskPriority::Second);
    FullTask ft1 = FullTask::create(gen.generateId(), t1);
    FullTask ft2 = FullTask::create(gen.generateId(), t2);
    auto sft = std::make_shared<FullTask>(ft2);
    ft1.addSubtask(sft);
    EXPECT_EQ(ft1.getParent().getId(), 0);
    EXPECT_EQ(sft->getParent().getId(), 0);
    EXPECT_EQ(sft->getId().getId(), 1);
}
TEST_F(FullTaskTest, shouldGetSubtasks) {
    Task t1 = Task::create(
            Date::create(2020, 7, 31),
            "name1",
            "",
            TaskPriority::None);
    Task t2 = Task::create(
            Date::create(2485, 3, 5),
            "name2",
            "label",
            TaskPriority::Second);
    FullTask ft1 = FullTask::create(TaskID::create(48), t1);
    FullTask ft2 = FullTask::create(TaskID::create(195), t2);
    auto sft = std::make_shared<FullTask>(ft2);
    ft1.addSubtask(sft);
    auto vec = ft1.getSubtasks();
    EXPECT_EQ(vec.size(), 1);
    EXPECT_TRUE(vec[0].getId()== ft2.getId().getId());
}

TEST_F(FullTaskTest, shouldEraseSubTask) {
    IDGenerator gen;
    Task t1 = Task::create(
            Date::create(2020, 7, 31),
            "name1",
            "",
            TaskPriority::None);
    Task t2 = Task::create(
            Date::create(2485, 3, 5),
            "name2",
            "label",
            TaskPriority::Second);
    FullTask ft1 = FullTask::create(gen.generateId(), t1);
    FullTask ft2 = FullTask::create(gen.generateId(), t2);
    auto sft = std::make_shared<FullTask>(ft2);
    ft1.addSubtask(sft);
    ft1.deleteSubtask(ft2.getId());
    auto vec = ft1.getSubtasks();
    EXPECT_EQ(vec.size(), 0);
}