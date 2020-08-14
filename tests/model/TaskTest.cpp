//
// Created by illia.dmitriiev on 7/27/2020.
//

#include <gtest/gtest.h>
#include "model/Task.h"

class TaskTest : public ::testing::Test {

};

TEST_F(TaskTest, shouldCreateTask) {
    boost::gregorian::date date(2020,7,23);
    std::string name = "name";
    std::string label = "label";
    TaskPriority tp = TaskPriority::Second;
    Task task = Task::create(date, name, label, tp);

    ASSERT_EQ(name, task.getName());
    ASSERT_EQ(label, task.getLabel());
    ASSERT_EQ(tp, task.getPriority());
}

TEST_F(TaskTest, shouldThrowExpception_1) {
    ASSERT_ANY_THROW(Task::create(
        boost::gregorian::date(1855, 14, 14),
        "dsfdgfhg",
        "aertys4gb5",
        TaskPriority::None)
    );
}

TEST_F(TaskTest, shouldThrowExpception_2) {
    ASSERT_ANY_THROW(Task::create(
        boost::gregorian::date(2100, 2, 29),
        "name",
        "label",
        TaskPriority::Third)
    );
}

TEST_F(TaskTest, sholdCompare_1) {
    ASSERT_FALSE(Task::Compare(
                Task::create(
                boost::gregorian::date(2100, 2, 27),
                "name",
                "label",
                TaskPriority::Third),
                Task::create(
                boost::gregorian::date(2100, 2, 28),
                "name",
                "label",
                TaskPriority::Third)
            )
    );
}

TEST_F(TaskTest, sholdCompare_2) {
    ASSERT_FALSE(Task::Compare(
            Task::create(
                    boost::gregorian::date(1500, 4, 27),
                    "name",
                    "label",
                    TaskPriority::Third),
            Task::create(
                    boost::gregorian::date(2178, 2, 27),
                    "name",
                    "LABEL",
                    TaskPriority::Third)
    )
    );
}

TEST_F(TaskTest, sholdCompare_3) {
    ASSERT_TRUE(Task::Compare(
            Task::create(
                    boost::gregorian::date(2000, 3, 31),
                    "name",
                    "label",
                    TaskPriority::None),
            Task::create(
                    boost::gregorian::date(2000, 3, 31),
                    "name",
                    "label",
                    TaskPriority::None)
    )
    );
}
