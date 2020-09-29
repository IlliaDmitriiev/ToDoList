//
// Created by Илля on 29.07.2020.
//

#include "ServiceTaskDTO.h"

ServiceTaskDTO ServiceTaskDTO::create(const TaskID &taskId, const boost::gregorian::date &date, const std::string &name, const std::string &label,
               TaskPriority priority){
    ServiceTaskDTO task(taskId, date, name, label, priority);
    return task;
}

ServiceTaskDTO ServiceTaskDTO::create(const boost::gregorian::date &date, const std::string &name, const std::string &label,
                        TaskPriority priority){
    ServiceTaskDTO task(date, name, label, priority);
    return task;
}

ServiceTaskDTO::ServiceTaskDTO(const TaskID &taskID, const boost::gregorian::date &date, const std::string &name, const std::string &label,
        TaskPriority priority) : id_(taskID), date_(date), name_(name), label_(label), priority_(priority), completed_(false){}

ServiceTaskDTO::ServiceTaskDTO(const boost::gregorian::date &date, const std::string &name, const std::string &label,
                 TaskPriority priority) : id_(TaskID::create(0)), date_(date),
                                        name_(name), label_(label), priority_(priority), completed_(false) {}


const boost::gregorian::date &ServiceTaskDTO::getDate() const {
    return date_;
}

const std::string &ServiceTaskDTO::getName() const {
    return name_;
}

const std::string &ServiceTaskDTO::getLabel() const {
    return label_;
}

TaskPriority ServiceTaskDTO::getPriority() const {
    return priority_;
}

const TaskID &ServiceTaskDTO::getId() const {
    return id_;
}

bool ServiceTaskDTO::isCompleted() const {
    return completed_;
}
