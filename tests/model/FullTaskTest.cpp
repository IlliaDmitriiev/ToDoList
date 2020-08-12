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
            Task::Priority::None);
    FullTask ft = FullTask::create(gen.generateId(), t);
    ASSERT_TRUE(Task::Compare(t, ft.getTask()));
}

TEST_F(FullTaskTest, shouldGetId) {
    IDGenerator gen;
    Task t = Task::create(
            Date::create(2020, 7, 31),
            "name1",
            "",
            Task::Priority::None);
    FullTask ft = FullTask::create(gen.generateId(), t);
    ASSERT_EQ(ft.getId().getId(),0);
}

TEST_F(FullTaskTest, shouldCreateParent) {
    IDGenerator gen;
    Task t1 = Task::create(
            Date::create(2020, 7, 31),
            "name1",
            "",
            Task::Priority::None);
    Task t2 = Task::create(
            Date::create(2485, 3, 5),
            "name2",
            "label",
            Task::Priority::Second);
    FullTask ft1 = FullTask::create(gen.generateId(), t1);
    FullTask ft2 = FullTask::create(gen.generateId(), t2);
    auto sft = std::make_shared<FullTask>(ft2);
    ft1.addSubtask(sft);
    ASSERT_EQ(ft1.getParent().getId(), 0);
    ASSERT_EQ(sft->getParent().getId(), 0);
    ASSERT_EQ(sft->getId().getId(), 1);
}

TEST_F(FullTaskTest, shouldEraseSubTask) {
    IDGenerator gen;
    Task t1 = Task::create(
            Date::create(2020, 7, 31),
            "name1",
            "",
            Task::Priority::None);
    Task t2 = Task::create(
            Date::create(2485, 3, 5),
            "name2",
            "label",
            Task::Priority::Second);
    FullTask ft1 = FullTask::create(gen.generateId(), t1);
    FullTask ft2 = FullTask::create(gen.generateId(), t2);
    auto sft = std::make_shared<FullTask>(ft2);
    ft1.addSubtask(sft);
    ft1.deleteSubtask(ft2.getId());
    ASSERT_TRUE(ft1.getSubTasks().find(ft1.getId())==ft1.getSubTasks().end());
}