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