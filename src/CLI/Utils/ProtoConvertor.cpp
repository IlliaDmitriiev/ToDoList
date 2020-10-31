//
// Created by ilya on 31.10.2020.
//

#include "ProtoConvertor.h"

TaskPriority ProtoConvertor::tranferToPriority(TaskStructure::Priority priority){
    if (TaskStructure_Priority_FIRST == priority){
        return TaskPriority::First;
    }
    else if (TaskStructure_Priority_SECOND == priority){
        return TaskPriority::Second;
    }
    else if (TaskStructure_Priority_THIRD == priority){
        return TaskPriority::Third;
    }
    else {
        return TaskPriority::None;
    }

}

TaskStructure::Priority ProtoConvertor::tranferToProtoPriority(TaskPriority priority){
    if (TaskPriority::First == priority){
        return TaskStructure_Priority_FIRST;
    }
    else if (TaskPriority::Second == priority){
        return TaskStructure_Priority_SECOND;
    }
    else if (TaskPriority::Third == priority){
        return TaskStructure_Priority_THIRD;
    }
    else {
        return TaskStructure_Priority_NONE;
    }
}

TaskDTO ProtoConvertor::transferToTaskDTO(const TaskStructure& message){
    return TaskDTO::create(TaskID::create(message.id()),
                           boost::gregorian::date(message.date()),
                           message.name(),
                           message.label(),
                           ProtoConvertor::tranferToPriority(message.prior()),
                           message.completed());
}

TaskStructure ProtoConvertor::transferToProtoTask(const TaskDTO& task){
    TaskStructure message;
    message.set_id(task.getId().ID());
    message.set_name(task.getName());
    message.set_label(task.getLabel());
    message.set_date(task.getDate().day_number());
    message.set_prior(ProtoConvertor::tranferToProtoPriority(task.getPriority()));
    message.set_completed(task.isCompleted());
    return message;
}

AddTaskResult ProtoConvertor::transferToReturnType(const AddTaskResponse &response){
    AddTaskResult type;
    if(response.success()){
        type.result = ResultType::SUCCESS;
        type.id = TaskID::create(response.created_id().id());
    }
    else {
        type.result= ResultType::FAILURE;
        type.error_message = response.error_message();
    }
    return type;
}

RequstTaskResult ProtoConvertor::transferToReturnType(const RequstTaskResponse& response){
    RequstTaskResult type;
    if(response.success()){
        type.result = ResultType::SUCCESS;
    }
    else {
        type.result = ResultType::FAILURE;
        type.error_message = response.error_message();
    }
    return type;
}