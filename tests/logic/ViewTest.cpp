//
// Created by Илля on 04.08.2020.
//


#include <gtest/gtest.h>
#include "logic/View.h"

const Task t1 = Task::create(
        Date::create(2020, 7, 31),
        "name1",
        "",
        Task::Priority::None);

const Task t2 = Task::create(
        Date::create(2020, 7, 31),
        "name2",
        "456578y&#&@)(#$?><</*-+fdg",
        Task::Priority::Second);


const Task t3 = Task::create(
        Date::create(1500, 2, 26),
        "name3",
        "label3",
        Task::Priority::Third);

const Task t4 = Task::create(
        Date::create(1500, 2, 28),
        "",
        "",
        Task::Priority::None);

class ViewTest : public ::testing::Test {
public:
    IDGenerator gen;

    std::shared_ptr<FullTask> sft1;
    std::shared_ptr<FullTask> sft2;
    std::shared_ptr<FullTask> sft3;
    std::shared_ptr<FullTask> sft4;

    ViewTest() {
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

TEST_F(ViewTest, shouldGetAllTasksByPrior) {
    View view;
    view.getViewByP().getStorage().putTaskInRightPlace(sft1);
    view.getViewByP().getStorage().putTaskInRightPlace(sft2);
    view.getViewByP().getStorage().putTaskInRightPlace(sft3);
    view.getViewByP().getStorage().putTaskInRightPlace(sft4);

    auto vec = view.getAllTasksByPrior();
    ASSERT_EQ(vec.size(), 4);
    ASSERT_TRUE(Task::Compare(vec[0].lock()->getTask(), t2));
    ASSERT_TRUE(Task::Compare(vec[1].lock()->getTask(), t3));
    ASSERT_TRUE(Task::Compare(vec[2].lock()->getTask(), t1));
    ASSERT_TRUE(Task::Compare(vec[3].lock()->getTask(), t4));
}

TEST_F(ViewTest, shouldGetAllTasksForToday) {
    View view;
    time_t now = time(0);
    auto cur = std::make_unique<tm>(*gmtime(&now));
    Date date = Date::create(cur->tm_year+1900, cur->tm_mon + 1, cur->tm_mday);

    Task t11 = Task::create(
            date,
            "name1",
            "456578y&#&@)(#$?><</*-+fdg",
            Task::Priority::Second);
    Task t12 = Task::create(
            date,
            "name2",
            "4565><</*-+fdg",
            Task::Priority::First);

    FullTask ft11 = FullTask::create(gen.generateId(), t11);
    FullTask ft12 = FullTask::create(gen.generateId(), t12);

    auto sft11 = std::make_shared<FullTask>(ft11);
    auto sft12 = std::make_shared<FullTask>(ft12);

    view.getViewByD().getStorage().addTask(sft11);
    view.getViewByD().getStorage().addTask(sft12);

    auto vec = view.getTasksForToday();

    ASSERT_EQ(vec.size(), 2);
    ASSERT_TRUE(Task::Compare(vec[0].lock()->getTask(), t12));
    ASSERT_TRUE(Task::Compare(vec[1].lock()->getTask(), t11));
}

TEST_F(ViewTest, shouldGetAllTasksForWeek) {
    View view;
    time_t now = time(0);
    auto cur = std::make_unique<tm>(*gmtime(&now));
    Date date1 = Date::create(cur->tm_year+1900, cur->tm_mon + 1, cur->tm_mday);
    Date date2 = Date::create(cur->tm_year+1900, cur->tm_mon + 1, cur->tm_mday);
    Date date3 = Date::create(cur->tm_year+1900, cur->tm_mon + 1, cur->tm_mday);
    int WeekDay1 = date1.getWday();
    if(WeekDay1 == 0) WeekDay1+=7;
    date1.moveWithinTheWeek(-WeekDay1 + 1);

    int WeekDay3 = date3.getWday();
    if(WeekDay3 == 0) WeekDay1+=7;

    Task t11 = Task::create(
            date1,
            "name1",
            "456578y&#&@)(#$?><</*-+fdg",
            Task::Priority::Second);
    Task t12 = Task::create(
            date2,
            "name2",
            "4565><</*-+fdg",
            Task::Priority::First);
    Task t13 = Task::create(
            date3,
            "name3",
            "",
            Task::Priority::None);
    FullTask ft11 = FullTask::create(gen.generateId(), t11);
    FullTask ft12 = FullTask::create(gen.generateId(), t12);
    FullTask ft13 = FullTask::create(gen.generateId(), t13);

    auto sft11 = std::make_shared<FullTask>(ft11);
    auto sft12 = std::make_shared<FullTask>(ft12);
    auto sft13 = std::make_shared<FullTask>(ft13);

    view.getViewByD().getStorage().addTask(sft11);
    view.getViewByD().getStorage().addTask(sft12);
    view.getViewByD().getStorage().addTask(sft13);

    auto vec = view.getTasksForWeek();

    ASSERT_EQ(vec.size(), 3);
    ASSERT_TRUE(Task::Compare(vec[0].lock()->getTask(), t11));
    ASSERT_TRUE(Task::Compare(vec[1].lock()->getTask(), t12));
    ASSERT_TRUE(Task::Compare(vec[2].lock()->getTask(), t13));
}

