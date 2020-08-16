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
        boost::gregorian::date date1{boost::gregorian::day_clock::local_day()};
        boost::gregorian::date date2;
        if (date1.day_of_week() == 0)
            date2 = boost::gregorian::date{date1.day_number()};
        else
            date2 = boost::gregorian::date{date1.day_number() + 7 - date1.day_of_week()};

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
    boost::gregorian::date date{boost::gregorian::day_clock::local_day()};

    EXPECT_TRUE(viewByDate.addTask(sft1));
    EXPECT_TRUE(viewByDate.addTask(sft3));
    EXPECT_TRUE(viewByDate.addTask(sft4));

    EXPECT_EQ(viewByDate.getTasksForToday(date).size(), 2);
}

TEST_F(ViewByDateTest, shouldGetAllTasksForToday2) {
    boost::gregorian::date date{boost::gregorian::day_clock::local_day()};

    EXPECT_TRUE(viewByDate.addTask(sft5));
    EXPECT_TRUE(viewByDate.addTask(sft6));

    EXPECT_EQ(viewByDate.getTasksForToday(date).size(), 2);
}

TEST_F(ViewByDateTest, shouldGetAllTasksForWeek1) {
    boost::gregorian::date date{boost::gregorian::day_clock::local_day()};

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
    boost::gregorian::date date{boost::gregorian::day_clock::local_day()};

    EXPECT_TRUE(viewByDate.getTasksForWeek(date).empty());
}
