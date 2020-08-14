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
            boost::gregorian::date(2020, 7, 31),
            "name1",
            "",
            TaskPriority::None);
    FullTask ft = FullTask::create(gen.generateId(), t);
    auto sft = std::make_shared<FullTask>(ft);
    TaskDTO td = con.transferToTaskDTO(sft);

    EXPECT_EQ(td.getId().getId(), 0);
    EXPECT_EQ(td.getPriority(), TaskPriority::None);
    EXPECT_EQ(td.getLabel(), "");
    EXPECT_EQ(td.getName(), "name1");
    EXPECT_EQ(td.getDate().year(), 2020);
    EXPECT_EQ(td.getDate().month(), 7);
    EXPECT_EQ(td.getDate().day(), 31);
}

TEST_F(TaskConvertorTest, shouldConvertTaskDTOIntoTask) {
    IDGenerator gen;
    TaskConvertor con;
    TaskDTO td = TaskDTO::create(
            boost::gregorian::date(2020, 7, 31),
            "name1",
            "",
            TaskPriority::None
            );

    Task t = con.transferToTask(td);

    EXPECT_EQ(td.getId().getId(), 0);
    EXPECT_EQ(td.getPriority(), TaskPriority::None);
    EXPECT_EQ(td.getLabel(), "");
    EXPECT_EQ(td.getName(), "name1");
    EXPECT_EQ(td.getDate().year(), 2020);
    EXPECT_EQ(td.getDate().month(), 7);
    EXPECT_EQ(td.getDate().day(), 31);
}
