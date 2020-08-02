//
// Created by Илля on 02.08.2020.
//

#include <gtest/gtest.h>
#include "IDGenerator.h"
#include "Convertor.h"

class ConvertorTest : public ::testing::Test {

};


TEST_F(ConvertorTest, shouldConvertFullTaskIntoDTO) {
    IDGenerator gen;
    Convertor con;

    Task t = Task::create(
            Date::create(2020, 7, 31),
            "name1",
            "",
            Task::Priority::None);
    FullTask ft = FullTask::create(gen, t);
    TaskDTO td = con.convert(ft);

    ASSERT_EQ(td.getTaskId().getId(), 0);
    ASSERT_EQ(td.getPrior(), Task::Priority::None);
    ASSERT_EQ(td.getLabel(), "");
    ASSERT_EQ(td.getName(), "name1");
    ASSERT_EQ(td.getDate().getYear(), 2020);
    ASSERT_EQ(td.getDate().getMounth(), 7);
    ASSERT_EQ(td.getDate().getDay(), 31);
}