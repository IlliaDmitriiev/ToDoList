//
// Created by illia.dmitriiev on 7/27/2020.
//

#include <gtest/gtest.h>
#include "Date.h"

class DateTest : public ::testing::Test {

};

TEST_F(DateTest, correctConstruction) {
    Date date = Date::create(2020, 7, 23);
    ASSERT_EQ(2020, date.getYear());
    ASSERT_EQ(7, date.getMounth());
    ASSERT_EQ(23, date.getDay());
}

TEST_F(DateTest, correctConstruction_MounthLessThan1) {
    ASSERT_ANY_THROW(Date::create(2020, 0, 23));
}

TEST_F(DateTest, correctConstruction_MounthMoreThan12) {
    ASSERT_ANY_THROW( Date::create(2020, 47, 23));
}

TEST_F(DateTest, correctConstruction_incorrectDay1) {
    ASSERT_ANY_THROW( Date::create(2020, 7, -5));
}

TEST_F(DateTest, correctConstruction_incorrectDay2) {
    ASSERT_ANY_THROW( Date::create(2020, 7, 0));
}

TEST_F(DateTest, correctConstruction_incorrectDay3) {
    ASSERT_ANY_THROW( Date::create(2020, 7, 32));
}

TEST_F(DateTest, correctConstruction_incorrectDay4) {
    ASSERT_ANY_THROW( Date::create(2019, 2, 29));
}

TEST_F(DateTest, correctConstruction_incorrectDay5) {
    ASSERT_ANY_THROW( Date::create(2020, 4, 31));
}

TEST_F(DateTest, correctConstruction_incorrectDay6) {
    ASSERT_ANY_THROW( Date::create(2020, 12, 175));
}

TEST_F(DateTest, correctConstruction_incorrectDay7) {
    ASSERT_ANY_THROW( Date::create(2020, 2, 30));
}

//WeekDay: 0 - sunday, 1 - monday ... 6 - saturday
TEST_F(DateTest, correctConstruction_correctWeekDay1) {
    Date date = Date::create(2020, 7, 23);
    ASSERT_EQ(4, date.getWday());
}

TEST_F(DateTest, correctConstruction_correctWeekDay2) {
    Date date = Date::create(2020, 5, 11);
    ASSERT_EQ(1, date.getWday());
}

TEST_F(DateTest, correctConstruction_correctWeekDay3) {
    Date date = Date::create(2020, 2, 29);
    ASSERT_EQ(6, date.getWday());
}

TEST_F(DateTest, correctConstruction_correctWeekDay4) {
    Date date = Date::create(2015, 10, 14);
    ASSERT_EQ(3, date.getWday());
}

TEST_F(DateTest, testFunc_moveWithinTheWeek) {
    Date date = Date::create(2020, 7, 29);
    for(int i = 1; i<=7; ++i) {
        int WeekDay = date.getWday();
        if (WeekDay == 0) WeekDay = 7;
        date.moveWithinTheWeek(i - WeekDay);
        if (i!=7) ASSERT_EQ(i, date.getWday());
        else ASSERT_EQ(0, date.getWday());
    }
}
