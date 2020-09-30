//
// Created by Илля on 30.07.2020.
//

#include <gtest/gtest.h>
#include "Core/api/ServiceTaskDTO.h"

class TaskDTOTest : public ::testing::Test {

};

TEST_F(TaskDTOTest, shouldCreate) {
    ServiceTaskDTO dto = ServiceTaskDTO::create(
            TaskID::create(47),
            boost::gregorian::date(2020, 7, 30),
            "name",
            "label",
            TaskPriority::None);
    EXPECT_EQ(47, dto.getId().getId());
    EXPECT_EQ(2020, dto.getDate().year());
    EXPECT_EQ(7, dto.getDate().month());
    EXPECT_EQ(30, dto.getDate().day());
    EXPECT_EQ("name", dto.getName());
    EXPECT_EQ("label", dto.getLabel());
    EXPECT_EQ(TaskPriority::None, dto.getPriority());
    EXPECT_EQ(false, dto.isCompleted());
}

TEST_F(TaskDTOTest, shouldCreate2) {
    ServiceTaskDTO dto = ServiceTaskDTO::create(
            boost::gregorian::date(2010, 10, 10),
            "",
            "label",
            TaskPriority::First);
    EXPECT_EQ(2010, dto.getDate().year());
    EXPECT_EQ(10, dto.getDate().month());
    EXPECT_EQ(10, dto.getDate().day());
    EXPECT_EQ("", dto.getName());
    EXPECT_EQ("label", dto.getLabel());
    EXPECT_EQ(TaskPriority::First, dto.getPriority());
    EXPECT_EQ(false, dto.isCompleted());
}

TEST_F(TaskDTOTest, shouldCreate3) {
    ServiceTaskDTO dto = ServiceTaskDTO::create(
            TaskID::create(47),
            boost::gregorian::date(2222, 10, 10),
            "",
            "",
            TaskPriority::First,
            true);
    EXPECT_EQ(47, dto.getId().getId());
    EXPECT_EQ(2222, dto.getDate().year());
    EXPECT_EQ(10, dto.getDate().month());
    EXPECT_EQ(10, dto.getDate().day());
    EXPECT_EQ("", dto.getName());
    EXPECT_EQ("", dto.getLabel());
    EXPECT_EQ(TaskPriority::First, dto.getPriority());
    EXPECT_EQ(true, dto.isCompleted());
}

TEST_F(TaskDTOTest, shouldThrowExeption_1) {
    EXPECT_ANY_THROW(ServiceTaskDTO::create(
            TaskID::create(47),
            boost::gregorian::date(2020, 7, 32),
            "name",
            "label",
            TaskPriority::None);
    );

}

TEST_F(TaskDTOTest, shouldThrowExeption_2) {
    EXPECT_ANY_THROW(ServiceTaskDTO::create(
            TaskID::create(47),
            boost::gregorian::date(2015, 2, 29),
            "name",
            "label",
            TaskPriority::None);
    );

}