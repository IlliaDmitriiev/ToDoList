//
// Created by ilya on 04.10.2020.
//

#include "ProtoTaskConvertor.h"
#include "PriorityConvertor.h"

ModelTaskDTO ProtoTaskConvertor::transferToModelTask(const TaskStructure& message){
    return ModelTaskDTO::create(TaskID::create(message.id()),
                                boost::gregorian::date(message.date()),
                                message.name(),
                                message.label(),
                                PriorityConvertor::tranferToPriority(message.prior()),
                                message.completed());
}

TaskStructure ProtoTaskConvertor::transferToTaskStructure(const ModelTaskDTO& task){
    TaskStructure message;
    message.set_id(task.getId().getId());
    message.set_name(task.getName());
    message.set_label(task.getLabel());
    message.set_date(task.getDate().day_number());
    message.set_prior(PriorityConvertor::tranferToProtoPriority(task.getPriority()));
    message.set_completed(task.isCompleted());
    return message;
}
