//
// Created by Илля on 29.07.2020.
//

#include "TaskDTO.h"

TaskDTO TaskDTO::create(const TaskID &taskId, const Date &date, const std::string &name, const std::string &label,
               Task::Priority prior){
    TaskDTO task(taskId, date, name, label, prior);
    return task;
}

TaskDTO::TaskDTO(const TaskID &taskId, const Date &date, const std::string &name, const std::string &label,
        Task::Priority prior) : taskID(taskId), date(date), name(name), label(label), prior(prior) {}

const TaskID &TaskDTO::getTaskId() const {
    return taskID;
}

const Date &TaskDTO::getDate() const {
    return date;
}

const std::string &TaskDTO::getName() const {
    return name;
}

const std::string &TaskDTO::getLabel() const {
    return label;
}

Task::Priority TaskDTO::getPrior() const {
    return prior;
}
