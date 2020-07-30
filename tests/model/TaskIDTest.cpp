//
// Created by Илля on 29.07.2020.
//


#include <gtest/gtest.h>
#include "TaskID.h"

class TaskIDTest : public ::testing::Test {

};

TEST_F(TaskIDTest, correctConstruction1) {
    TaskID taskID = TaskID::create(5);
    ASSERT_EQ(5, taskID.getId());
}

TEST_F(TaskIDTest, correctConstruction2) {
    TaskID taskID = TaskID::create(105478);
    ASSERT_EQ(105478, taskID.getId());
}

TEST_F(TaskIDTest, correctConstruction3) {
    TaskID taskID = TaskID::create(-7);
    ASSERT_EQ(-7, taskID.getId());
}

TEST_F(TaskIDTest, correctHasher1) {
    TaskID taskID = TaskID::create(15);
    TaskID::Hasher h;
    ASSERT_EQ(15, h(taskID));
}

TEST_F(TaskIDTest, correctHasher2) {
    TaskID taskID = TaskID::create(0);
    TaskID::Hasher h;
    ASSERT_EQ(0, h(taskID));
}

TEST_F(TaskIDTest, correctComparator1) {
    TaskID taskID1 = TaskID::create(15);
    TaskID taskID2 = TaskID::create(-15);
    TaskID::Comparator cmp;
    ASSERT_FALSE(cmp(taskID1, taskID2));
}

TEST_F(TaskIDTest, correctComparator2) {
    TaskID taskID1 = TaskID::create(47);
    TaskID taskID2 = TaskID::create(47);
    TaskID::Comparator cmp;
    ASSERT_TRUE(cmp(taskID1, taskID2));
}