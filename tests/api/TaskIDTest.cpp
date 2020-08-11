//
// Created by Илля on 29.07.2020.
//


#include <gtest/gtest.h>
#include "api/TaskID.h"

class TaskIDTest : public ::testing::Test {

};

TEST_F(TaskIDTest, shouldCreateObj1) {
    TaskID taskID = TaskID::create(5);
    ASSERT_EQ(5, taskID.getId());
}

TEST_F(TaskIDTest, shouldCreateObj2) {
    TaskID taskID = TaskID::create(105478);
    ASSERT_EQ(105478, taskID.getId());
}



TEST_F(TaskIDTest, shouldHash1) {
    TaskID taskID = TaskID::create(15);
    TaskID::Hasher h;
    ASSERT_EQ(15, h(taskID));
}

TEST_F(TaskIDTest, shouldHash2) {
    TaskID taskID = TaskID::create(0);
    TaskID::Hasher h;
    ASSERT_EQ(0, h(taskID));
}

TEST_F(TaskIDTest, shouldCompare1) {
    TaskID taskID1 = TaskID::create(15);
    TaskID taskID2 = TaskID::create(145);
    TaskID::Comparator cmp;
    ASSERT_FALSE(cmp(taskID1, taskID2));
}

TEST_F(TaskIDTest, shouldCompare2) {
    TaskID taskID1 = TaskID::create(47);
    TaskID taskID2 = TaskID::create(47);
    TaskID::Comparator cmp;
    ASSERT_TRUE(cmp(taskID1, taskID2));
}

TEST_F(TaskIDTest, shouldThrowExeption) {
    ASSERT_ANY_THROW(TaskID::create(-4););
}