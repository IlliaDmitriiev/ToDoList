//
// Created by Илля on 29.07.2020.
//

#include "TaskDTO.h"

TaskDTO TaskDTO::create(const TaskID &taskId, const BoostDate &date, const std::string &name, const std::string &label,
               TaskPriority priority){
    TaskDTO task(taskId, date, name, label, priority);
    return task;
}

TaskDTO TaskDTO::create(const BoostDate &date, const std::string &name, const std::string &label,
                        TaskPriority priority){
    TaskDTO task(date, name, label, priority);
    return task;
}

TaskDTO::TaskDTO(const TaskID &taskID, const BoostDate &date, const std::string &name, const std::string &label,
        TaskPriority priority) : id_(taskID), date_(date), name_(name), label_(label), priority_(priority), completed_(false){}

TaskDTO::TaskDTO(const BoostDate &date, const std::string &name, const std::string &label,
                 TaskPriority priority) : id_(TaskID::create(0)), date_(date),
                                        name_(name), label_(label), priority_(priority), completed_(false) {}


const BoostDate &TaskDTO::getDate() const {
    return date_;
}

const std::string &TaskDTO::getName() const {
    return name_;
}

const std::string &TaskDTO::getLabel() const {
    return label_;
}

TaskPriority TaskDTO::getPriority() const {
    return priority_;
}

const TaskID &TaskDTO::getId() const {
    return id_;
}

bool TaskDTO::isCompleted() const {
    return completed_;
}
