//
// Created by Илля on 29.07.2020.
//

#include <gtest/gtest.h>
#include "Core/model/logic/IDGenerator.h"

class IDGeneratorTest : public ::testing::Test {

};


TEST_F(IDGeneratorTest, shouldGenerate) {
    IDGenerator gen;
    ASSERT_EQ(0, gen.generateId().getId());
    ASSERT_EQ(1, gen.generateId().getId());
}


