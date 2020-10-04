//
// Created by ilya on 04.10.2020.
//

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Core/persistence/PriorityConvertor.h"

class PriorityConvertorTest : public ::testing::Test {

};

TEST_F(PriorityConvertorTest, shouldConvert1) {
    auto obj1 = TaskStructure_Priority_FIRST;
    auto obj2 = TaskStructure_Priority_SECOND;
    auto obj3 = TaskStructure_Priority_THIRD;
    auto obj4 = TaskStructure_Priority_NONE;
    EXPECT_EQ(PriorityConvertor::tranferToPriority(obj1), TaskPriority::First);
    EXPECT_EQ(PriorityConvertor::tranferToPriority(obj2), TaskPriority::Second);
    EXPECT_EQ(PriorityConvertor::tranferToPriority(obj3), TaskPriority::Third);
    EXPECT_EQ(PriorityConvertor::tranferToPriority(obj4), TaskPriority::None);
}

TEST_F(PriorityConvertorTest, shouldConvert2) {
    auto obj1 = TaskPriority::First;
    auto obj2 = TaskPriority::Second;
    auto obj3 = TaskPriority::Third;
    auto obj4 = TaskPriority::None;
    EXPECT_EQ(PriorityConvertor::tranferToProtoPriority(obj1), TaskStructure_Priority_FIRST);
    EXPECT_EQ(PriorityConvertor::tranferToProtoPriority(obj2), TaskStructure_Priority_SECOND);
    EXPECT_EQ(PriorityConvertor::tranferToProtoPriority(obj3), TaskStructure_Priority_THIRD);
    EXPECT_EQ(PriorityConvertor::tranferToProtoPriority(obj4), TaskStructure_Priority_NONE);
}
