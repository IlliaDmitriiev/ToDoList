//
// Created by ilya on 04.10.2020.
//

#include <gtest/gtest.h>
#include "Core/utils/Convertors/ProtoTaskConvertor.h"

class ProtoTaskConvertorTest : public ::testing::Test {

};

TEST_F(ProtoTaskConvertorTest, shouldConvert1) {
    auto task = ModelTaskDTO::create(TaskID::create(47),
                                     boost::gregorian::date(2020, 10, 10),
                                     "name",
                                     "label",
                                     TaskPriority::None,
                                     true);

    auto proto = ProtoTaskConvertor::transferToTaskStructure(task);
    EXPECT_EQ(proto.name(), task.getName());
    EXPECT_EQ(proto.label(), task.getLabel());
    EXPECT_EQ(proto.date(), task.getDate().day_number());
    EXPECT_EQ(proto.completed(), task.isCompleted());
    EXPECT_EQ(proto.prior(), TaskStructure::NONE);
}

TEST_F(ProtoTaskConvertorTest, shouldConvert2) {
    TaskStructure proto;
    proto.set_prior(TaskStructure::FIRST);
    proto.set_name("name");
    proto.set_label("label");
    proto.set_date(boost::gregorian::date(2020, 10, 10).day_number());
    proto.set_completed(false);
    auto task = ProtoTaskConvertor::transferToModelTask(proto);
    EXPECT_EQ(proto.name(), task.getName());
    EXPECT_EQ(proto.label(), task.getLabel());
    EXPECT_EQ(proto.date(), task.getDate().day_number());
    EXPECT_EQ(proto.completed(), task.isCompleted());
    EXPECT_EQ(TaskPriority::First, task.getPriority());
}

