//
// Created by Илля on 02.08.2020.
//

#include <gtest/gtest.h>
#include "Core/logic/IDGenerator.h"
#include "Core/utils/TaskConvertor.h"

class TaskConvertorTest : public ::testing::Test {

};


TEST_F(TaskConvertorTest, shouldConvert1) {

    auto model_task = ModelTaskDTO::create(TaskID::create(5),
                                           boost::gregorian::date(2020,10,10),
                                           "name",
                                           "label",
                                           TaskPriority::Second,
                                           true);
    auto task = TaskConvertor::transferToServiceDTO(model_task);

    EXPECT_EQ(task.getId().getId(), model_task.getId().getId());
    EXPECT_EQ(task.getPriority(), model_task.getPriority());
    EXPECT_EQ(task.getLabel(), model_task.getLabel());
    EXPECT_EQ(task.getName(), model_task.getName());
    EXPECT_EQ(task.getDate(), model_task.getDate());
    EXPECT_EQ(task.isCompleted(), model_task.isCompleted());
}

TEST_F(TaskConvertorTest, shouldConvert2) {

    auto task = ServiceTaskDTO::create(TaskID::create(5),
                                           boost::gregorian::date(2020,10,10),
                                           "name",
                                           "label",
                                           TaskPriority::Second,
                                           true);
    auto model_task = TaskConvertor::transferToModelDTO(task);

    EXPECT_EQ(task.getId().getId(), model_task.getId().getId());
    EXPECT_EQ(task.getPriority(), model_task.getPriority());
    EXPECT_EQ(task.getLabel(), model_task.getLabel());
    EXPECT_EQ(task.getName(), model_task.getName());
    EXPECT_EQ(task.getDate(), model_task.getDate());
    EXPECT_EQ(task.isCompleted(), model_task.isCompleted());
}
