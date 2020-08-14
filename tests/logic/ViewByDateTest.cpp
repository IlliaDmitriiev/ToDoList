//
// Created by Илля on 03.08.2020.
//

#include <gtest/gtest.h>
#include "logic/ViewByDate.h"

class ViewByDateTest : public ::testing::Test {
public:
    ViewByDate viewByDate;
    IDGenerator gen;

    std::shared_ptr<FullTask> sft1;
    std::shared_ptr<FullTask> sft2;
    std::shared_ptr<FullTask> sft3;
    std::shared_ptr<FullTask> sft4;
    std::shared_ptr<FullTask> sft5;
    std::shared_ptr<FullTask> sft6;


    void SetUp() override {
        time_t now = time(0);
        auto cur = std::make_unique<tm>(*gmtime(&now));
        boost::gregorian::date date1(cur->tm_year+1900, cur->tm_mon + 1, cur->tm_mday);
        boost::gregorian::date date2(date1.day_number() + 7 - (date1.week_number() + 7) % 7);

        const Task t1 = Task::create(
                date1,
                "name1",
                "",
                TaskPriority::None);

        const Task t2 = Task::create(
                date2,
                "name2",
                "456578y&#&@)(#$?><</*-+fdg",
                TaskPriority::Second);


        const Task t3 = Task::create(
                boost::gregorian::date(1500, 2, 26),
                "name3",
                "label3",
                TaskPriority::Third);

        const Task t4 = Task::create(
                date1,
                "name4",
                "",
                TaskPriority::First);

        const Task t5 = Task::create(
                date1,
                "name5",
                "LABEL%^",
                TaskPriority::Second);

        const Task t6 = Task::create(
                date1,
                "name6",
                "label6",
                TaskPriority::Third);


        FullTask ft1 = FullTask::create(gen.generateId(), t1);
        FullTask ft2 = FullTask::create(gen.generateId(), t2);
        FullTask ft3 = FullTask::create(gen.generateId(), t3);
        FullTask ft4 = FullTask::create(gen.generateId(), t4);
        FullTask ft5 = FullTask::create(gen.generateId(), t5);
        FullTask ft6 = FullTask::create(gen.generateId(), t6);

        sft1 = std::make_shared<FullTask>(ft1);
        sft2 = std::make_shared<FullTask>(ft2);
        sft3 = std::make_shared<FullTask>(ft3);
        sft4 = std::make_shared<FullTask>(ft4);
        sft5 = std::make_shared<FullTask>(ft5);
        sft6 = std::make_shared<FullTask>(ft6);

    }

};

TEST_F(ViewByDateTest, shouldAddTask) {
    EXPECT_TRUE(viewByDate.addTask(sft1));
    EXPECT_TRUE(viewByDate.addTask(sft2));
    EXPECT_TRUE(viewByDate.addTask(sft3));
}

TEST_F(ViewByDateTest, shouldDelete) {
    EXPECT_TRUE(viewByDate.addTask(sft1));
    EXPECT_TRUE(viewByDate.addTask(sft2));

    EXPECT_TRUE(viewByDate.deleteTask(sft1));
}

TEST_F(ViewByDateTest, shouldNotDelete) {
    EXPECT_FALSE(viewByDate.deleteTask(sft1));
    EXPECT_FALSE(viewByDate.deleteTask(sft3));
}

TEST_F(ViewByDateTest, shouldGetEmptyVector) {
    EXPECT_TRUE(viewByDate.getAllTasksByPrior().empty());
}

TEST_F(ViewByDateTest, shouldGetAllTasksForToday1) {
    time_t now = time(0);
    auto cur = std::make_unique<tm>(*gmtime(&now));
    boost::gregorian::date date(cur->tm_year+1900, cur->tm_mon + 1, cur->tm_mday);

    EXPECT_TRUE(viewByDate.addTask(sft1));
    EXPECT_TRUE(viewByDate.addTask(sft2));
    EXPECT_TRUE(viewByDate.addTask(sft3));
    EXPECT_TRUE(viewByDate.addTask(sft4));

    EXPECT_EQ(viewByDate.getTasksForToday(date).size(), 2);
}

TEST_F(ViewByDateTest, shouldGetAllTasksForToday2) {
    time_t now = time(0);
    auto cur = std::make_unique<tm>(*gmtime(&now));
    boost::gregorian::date date(cur->tm_year+1900, cur->tm_mon + 1, cur->tm_mday);

    EXPECT_TRUE(viewByDate.addTask(sft5));
    EXPECT_TRUE(viewByDate.addTask(sft6));

    EXPECT_EQ(viewByDate.getTasksForToday(date).size(), 2);
}

TEST_F(ViewByDateTest, shouldGetAllTasksForWeek1) {
    time_t now = time(0);
    auto cur = std::make_unique<tm>(*gmtime(&now));
    boost::gregorian::date date(cur->tm_year+1900, cur->tm_mon + 1, cur->tm_mday);

    EXPECT_TRUE(viewByDate.addTask(sft1));
    EXPECT_TRUE(viewByDate.addTask(sft2));
    EXPECT_TRUE(viewByDate.addTask(sft3));
    EXPECT_TRUE(viewByDate.addTask(sft4));

    EXPECT_EQ(viewByDate.getTasksForWeek(date).size(), 3);
}

TEST_F(ViewByDateTest, shouldGetAllTasksForWeek2) {

    EXPECT_TRUE(viewByDate.addTask(sft1));
    EXPECT_TRUE(viewByDate.addTask(sft2));
    EXPECT_TRUE(viewByDate.addTask(sft3));
    EXPECT_TRUE(viewByDate.addTask(sft4));

    EXPECT_EQ(viewByDate.getTasksForWeek(boost::gregorian::date(1500, 2, 26)).size(), 1);
}

TEST_F(ViewByDateTest, shouldGetAllTasksForWeek3) {
    time_t now = time(0);
    auto cur = std::make_unique<tm>(*gmtime(&now));
    boost::gregorian::date date(cur->tm_year+1900, cur->tm_mon + 1, cur->tm_mday);

    EXPECT_TRUE(viewByDate.getTasksForWeek(date).empty());
}
