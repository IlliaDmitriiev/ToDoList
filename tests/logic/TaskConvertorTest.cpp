//
// Created by Илля on 02.08.2020.
//

#include <gtest/gtest.h>
#include "logic/IDGenerator.h"
#include "logic/TaskConvertor.h"

class TaskConvertorTest : public ::testing::Test {

};


TEST_F(TaskConvertorTest, shouldConvertFullTaskIntoDTO) {
    IDGenerator gen;
    TaskConvertor con;

    Task t = Task::create(
            Date::create(2020, 7, 31),
            "name1",
            "",
            Task::Priority::None);
    FullTask ft = FullTask::create(gen.generateId(), t);
    auto sft = std::make_shared<FullTask>(ft);
    TaskDTO td = con.transferToTaskDTO(sft);

    EXPECT_EQ(td.getTaskId().getId(), 0);
    EXPECT_EQ(td.getPrior(), Task::Priority::None);
    EXPECT_EQ(td.getLabel(), "");
    EXPECT_EQ(td.getName(), "name1");
    EXPECT_EQ(td.getDate().getYear(), 2020);
    EXPECT_EQ(td.getDate().getMounth(), 7);
    EXPECT_EQ(td.getDate().getDay(), 31);
}

TEST_F(TaskConvertorTest, shouldConvertTaskDTOIntoTask) {
    IDGenerator gen;
    TaskConvertor con;
    TaskDTO td = TaskDTO::create(
            Date::create(2020, 7, 31),
            "name1",
            "",
            Task::Priority::None
            );

    Task t = con.transferToTask(td);

    EXPECT_EQ(td.getTaskId().getId(), 0);
    EXPECT_EQ(td.getPrior(), Task::Priority::None);
    EXPECT_EQ(td.getLabel(), "");
    EXPECT_EQ(td.getName(), "name1");
    EXPECT_EQ(td.getDate().getYear(), 2020);
    EXPECT_EQ(td.getDate().getMounth(), 7);
    EXPECT_EQ(td.getDate().getDay(), 31);
}