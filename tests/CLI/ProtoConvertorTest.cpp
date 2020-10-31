//
// Created by ilya on 31.10.2020.
//

#include <gtest/gtest.h>
#include "CLI/Utils/ProtoConvertor.h"

class ProtoConvertorTest : public ::testing::Test {
public:
};

TEST_F(ProtoConvertorTest, shouldTransferToReturnType1) {
    RequstTaskResponse response;
    response.set_success(true);
    auto type = ProtoConvertor::transferToReturnType(response);
    EXPECT_EQ(type.result, ResultType::SUCCESS);
}


TEST_F(ProtoConvertorTest, shouldTransferToReturnType2) {
    RequstTaskResponse response;
    response.set_success(false);
    response.set_error_message("error message");
    auto type = ProtoConvertor::transferToReturnType(response);
    EXPECT_EQ(type.result, ResultType::FAILURE);
    EXPECT_EQ(type.error_message, "error message");
}


TEST_F(ProtoConvertorTest, shouldTransferToReturnType3) {
    AddTaskResponse response;
    response.set_success(true);
    response.set_allocated_created_id(new TaskIDRequest);
    response.mutable_created_id()->set_id(5);
    auto type = ProtoConvertor::transferToReturnType(response);
    EXPECT_EQ(type.result, ResultType::SUCCESS);
    EXPECT_EQ(type.id.value().ID(), response.created_id().id());
}


TEST_F(ProtoConvertorTest, shouldTransferToReturnType4) {
    AddTaskResponse response;
    response.set_success(false);
    response.set_error_message("error message");
    auto type = ProtoConvertor::transferToReturnType(response);
    EXPECT_EQ(type.result, ResultType::FAILURE);
    EXPECT_EQ(type.error_message, "error message");
}

TEST_F(ProtoConvertorTest, shouldTranferToPriority){
    auto priority_none = ProtoConvertor::tranferToPriority(TaskStructure::NONE);
    auto priority_first = ProtoConvertor::tranferToPriority(TaskStructure::FIRST);
    auto priority_second = ProtoConvertor::tranferToPriority(TaskStructure::SECOND);
    auto priority_third = ProtoConvertor::tranferToPriority(TaskStructure::THIRD);
    EXPECT_EQ(priority_none,TaskPriority::None);
    EXPECT_EQ(priority_first,TaskPriority::First);
    EXPECT_EQ(priority_second,TaskPriority::Second);
    EXPECT_EQ(priority_third,TaskPriority::Third);
}

TEST_F(ProtoConvertorTest, shouldTranferToProtoPriority){
    auto priority_none = ProtoConvertor::tranferToProtoPriority(TaskPriority::None);
    auto priority_first = ProtoConvertor::tranferToProtoPriority(TaskPriority::First);
    auto priority_second = ProtoConvertor::tranferToProtoPriority(TaskPriority::Second);
    auto priority_third = ProtoConvertor::tranferToProtoPriority(TaskPriority::Third);
    EXPECT_EQ(priority_none,TaskStructure::NONE);
    EXPECT_EQ(priority_first,TaskStructure::FIRST);
    EXPECT_EQ(priority_second,TaskStructure::SECOND);
    EXPECT_EQ(priority_third,TaskStructure::THIRD);
}

TEST_F(ProtoConvertorTest, shouldTransferToTaskDTO) {
    int date = boost::gregorian::date(2020, 10, 10).day_number();
    TaskStructure task;
    task.set_name("name");
    task.set_label("label");
    task.set_prior(TaskStructure::NONE);
    task.set_completed(true);
    task.set_date(date);
    auto dto = ProtoConvertor::transferToTaskDTO(task);
    EXPECT_EQ(dto.getDate().day_number(), date);
    EXPECT_EQ(dto.getName(), "name");
    EXPECT_EQ(dto.getLabel(), "label");
    EXPECT_EQ(dto.getPriority(), TaskPriority::None);
    EXPECT_EQ(dto.isCompleted(), true);
}

TEST_F(ProtoConvertorTest, shouldTransferToProtoTask){
    boost::gregorian::date date(2020, 10, 10);
    auto dto = TaskDTO::create(TaskID::create(5),
                               date,
                               "name",
                               "label",
                               TaskPriority::Second,
                               false);
    auto proto_task = ProtoConvertor::transferToProtoTask(dto);
    EXPECT_EQ(proto_task.name(),"name");
    EXPECT_EQ(proto_task.label(),"label");
    EXPECT_EQ(proto_task.prior(), TaskStructure::SECOND);
    EXPECT_EQ(proto_task.completed(), false);
    EXPECT_EQ(proto_task.date(), date.day_number());
}
