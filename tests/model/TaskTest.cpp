//
// Created by illia.dmitriiev on 7/27/2020.
//

#include <gtest/gtest.h>
#include "Task.h"

class TaskTest : public ::testing::Test {

};

TEST_F(TaskTest, testConstruction1) {
    Date date = Date::create(2020,7,23);
    std::string name = "name";
    std::string label = "label";
    Task::Priority tp = Task::Priority::Second;
    Task task = Task::create(date, name, label, tp);

    ASSERT_EQ(name, task.getName());
    ASSERT_EQ(label, task.getLabel());
    ASSERT_EQ(tp, task.getPrior());
}

TEST_F(TaskTest, testConstruction2) {
    ASSERT_ANY_THROW(Task::create(
        Date::create(1855, 14, 14),
        "dsfdgfhg",
        "aertys4gb5",
        Task::Priority::None)
    );
}

TEST_F(TaskTest, testConstruction3) {
    ASSERT_ANY_THROW(Task::create(
        Date::create(2100, 2, 29),
        "name",
        "label",
        Task::Priority::Third)
    );
}
