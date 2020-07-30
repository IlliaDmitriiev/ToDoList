//
// Created by Илля on 30.07.2020.
//

#include <gtest/gtest.h>
#include "TaskDTO.h"

class TaskDTOTest : public ::testing::Test {

};

TEST_F(TaskDTOTest, CorrectConstruction1) {
    TaskDTO dto = TaskDTO::create(
            TaskID::create(47),
            Date::create(2020, 7, 30),
            "name",
            "label",
            Task::Priority::None);
    ASSERT_EQ(47, dto.getTaskId().getId());
    ASSERT_EQ(2020, dto.getDate().getYear());
    ASSERT_EQ(7, dto.getDate().getMounth());
    ASSERT_EQ(30, dto.getDate().getDay());
    ASSERT_EQ("name", dto.getName());
    ASSERT_EQ("label", dto.getLabel());
    ASSERT_EQ(Task::Priority::None, dto.getPrior());
}

TEST_F(TaskDTOTest, CorrectConstruction2) {
    ASSERT_ANY_THROW(TaskDTO::create(
            TaskID::create(47),
            Date::create(2020, 7, 32),
            "name",
            "label",
            Task::Priority::None);
    );

}

TEST_F(TaskDTOTest, CorrectConstruction3) {
    ASSERT_ANY_THROW(TaskDTO::create(
            TaskID::create(47),
            Date::create(2015, 2, 29),
            "name",
            "label",
            Task::Priority::None);
    );

}