//
// Created by illia.dmitriiev on 8/4/2020.
//

#include <gtest/gtest.h>
#include "logic/Cleaner.h"


class CleanerTest : public ::testing::Test {

};

TEST_F(CleanerTest, shouldTestUpdateFunc) {
   Cleaner cl;
    cl.increaseTotalCount(20);
    ASSERT_FALSE(cl.isItTimeToUpdate());
    cl.increaseDeletedCount(4);
    ASSERT_TRUE(cl.isItTimeToUpdate());
}
