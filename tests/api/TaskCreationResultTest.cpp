//
// Created by Илля on 08.08.2020.
//

#include <gtest/gtest.h>
#include "api/TaskCreationResult.h"

class TaskCreationResultTest : public ::testing::Test {

};

TEST_F(TaskCreationResultTest, shouldCreateSuccess) {
    TaskCreationResult tcr = TaskCreationResult::success(TaskID::create(47));
    ASSERT_EQ(TaskID::create(47).getId(), tcr.getTaskID().value().getId());
    ASSERT_FALSE(tcr.getErrorMessage().has_value());
}


TEST_F(TaskCreationResultTest, shouldNotFoundTask) {
    TaskCreationResult tcr = TaskCreationResult::taskNotFound();
    ASSERT_FALSE(tcr.getTaskID().has_value());
    ASSERT_FALSE(tcr.getErrorMessage().has_value());
}

TEST_F(TaskCreationResultTest, shouldGetErrorMessage) {
    TaskCreationResult tcr = TaskCreationResult::error("3345#$%*JEDM5");
    ASSERT_FALSE(tcr.getTaskID().has_value());
    ASSERT_EQ(tcr.getErrorMessage().value(),"3345#$%*JEDM5");
}

