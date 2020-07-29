//
// Created by Илля on 29.07.2020.
//

#include <gtest/gtest.h>
#include "IDGenerator.h"

class IDGeneratorTest : public ::testing::Test {

};

TEST_F(IDGeneratorTest, IdGeneratingFromNumber) {
    IDGenerator gen(41515);
    ASSERT_EQ(41515, gen.generateId().getId());
    ASSERT_EQ(41516, gen.generateId().getId());
}

TEST_F(IDGeneratorTest, IdGeneratingDefault) {
    IDGenerator gen;
    ASSERT_EQ(0, gen.generateId().getId());
    ASSERT_EQ(1, gen.generateId().getId());
}

TEST_F(IDGeneratorTest, IdGeneratingWithNegativeNumber) {
    IDGenerator gen(-4);
    ASSERT_EQ(-4, gen.generateId().getId());
    ASSERT_EQ(-3, gen.generateId().getId());
}
