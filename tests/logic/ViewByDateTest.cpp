//
// Created by Илля on 03.08.2020.
//

#include <gtest/gtest.h>
#include "logic/ViewByDate.h"

class ViewByDateTest : public ::testing::Test {
public:
    ViewByDate storage;
    IDGenerator gen;

    std::shared_ptr<FullTask> sft1;
    std::shared_ptr<FullTask> sft2;
    std::shared_ptr<FullTask> sft3;
    std::shared_ptr<FullTask> sft4;


    void SetUp() override {
        time_t now = time(0);
        auto cur = std::make_unique<tm>(*gmtime(&now));
        Date date1 = Date::create(cur->tm_year+1900, cur->tm_mon + 1, cur->tm_mday);
        Date date2 = date1;

        int weekDay = date2.getWday();
        if (weekDay == 0) weekDay = 7;
        date2.moveWithinTheWeek(7 - weekDay);

        const Task t1 = Task::create(
                date1,
                "name1",
                "",
                Task::Priority::None);

        const Task t2 = Task::create(
                date2,
                "name2",
                "456578y&#&@)(#$?><</*-+fdg",
                Task::Priority::Second);


        const Task t3 = Task::create(
                Date::create(1500, 2, 26),
                "name3",
                "label3",
                Task::Priority::Third);

        const Task t4 = Task::create(
                date1,
                "name4",
                "",
                Task::Priority::First);


        FullTask ft1 = FullTask::create(gen.generateId(), t1);
        FullTask ft2 = FullTask::create(gen.generateId(), t2);
        FullTask ft3 = FullTask::create(gen.generateId(), t3);
        FullTask ft4 = FullTask::create(gen.generateId(), t4);

        sft1 = std::make_shared<FullTask>(ft1);
        sft2 = std::make_shared<FullTask>(ft2);
        sft3 = std::make_shared<FullTask>(ft3);
        sft4 = std::make_shared<FullTask>(ft4);

    }

};

TEST_F(ViewByDateTest, shouldAddTask) {
    EXPECT_NO_THROW(storage.addTask(sft1));
    EXPECT_NO_THROW(storage.addTask(sft2));
    EXPECT_NO_THROW(storage.addTask(sft3));
}

TEST_F(ViewByDateTest, shouldDelete) {
    EXPECT_NO_THROW(storage.addTask(sft1));
    EXPECT_NO_THROW(storage.addTask(sft2));

    EXPECT_TRUE(storage.deleteTask(sft1));
}

TEST_F(ViewByDateTest, shouldNotDelete) {
    EXPECT_FALSE(storage.deleteTask(sft1));
    EXPECT_FALSE(storage.deleteTask(sft3));
}

TEST_F(ViewByDateTest, shouldGetEmptyVector) {
    EXPECT_TRUE(storage.getAllTasksByPrior().empty());
}

TEST_F(ViewByDateTest, shouldGetAllTasksForToday) {
    time_t now = time(0);
    auto cur = std::make_unique<tm>(*gmtime(&now));
    Date date = Date::create(cur->tm_year+1900, cur->tm_mon + 1, cur->tm_mday);

    EXPECT_NO_THROW(storage.addTask(sft1));
    EXPECT_NO_THROW(storage.addTask(sft2));
    EXPECT_NO_THROW(storage.addTask(sft3));
    EXPECT_NO_THROW(storage.addTask(sft4));

    EXPECT_EQ(storage.getTasksForToday(date).size(), 2);
}

TEST_F(ViewByDateTest, shouldGetAllTasksForWeek1) {
    time_t now = time(0);
    auto cur = std::make_unique<tm>(*gmtime(&now));
    Date date = Date::create(cur->tm_year+1900, cur->tm_mon + 1, cur->tm_mday);

    EXPECT_NO_THROW(storage.addTask(sft1));
    EXPECT_NO_THROW(storage.addTask(sft2));
    EXPECT_NO_THROW(storage.addTask(sft3));
    EXPECT_NO_THROW(storage.addTask(sft4));

    EXPECT_EQ(storage.getTasksForWeek(date).size(), 3);
}

TEST_F(ViewByDateTest, shouldGetAllTasksForWeek2) {

    EXPECT_NO_THROW(storage.addTask(sft1));
    EXPECT_NO_THROW(storage.addTask(sft2));
    EXPECT_NO_THROW(storage.addTask(sft3));
    EXPECT_NO_THROW(storage.addTask(sft4));

    EXPECT_EQ(storage.getTasksForWeek(Date::create(1500, 2, 26)).size(), 1);
}

TEST_F(ViewByDateTest, shouldGetAllTasksForWeek3) {
    time_t now = time(0);
    auto cur = std::make_unique<tm>(*gmtime(&now));
    Date date = Date::create(cur->tm_year+1900, cur->tm_mon + 1, cur->tm_mday);

    EXPECT_TRUE(storage.getTasksForWeek(date).empty());
}
