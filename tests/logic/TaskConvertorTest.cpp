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

    ASSERT_EQ(td.getTaskId().getId(), 0);
    ASSERT_EQ(td.getPrior(), Task::Priority::None);
    ASSERT_EQ(td.getLabel(), "");
    ASSERT_EQ(td.getName(), "name1");
    ASSERT_EQ(td.getDate().getYear(), 2020);
    ASSERT_EQ(td.getDate().getMounth(), 7);
    ASSERT_EQ(td.getDate().getDay(), 31);
}