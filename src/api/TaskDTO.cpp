//
// Created by Илля on 29.07.2020.
//

#include "TaskDTO.h"

TaskDTO TaskDTO::create(const TaskID &taskId, const Date &date, const std::string &name, const std::string &label,
               Task::Priority prior){
    TaskDTO task(taskId, date, name, label, prior);
    return task;
}

TaskDTO TaskDTO::create(const Date &date, const std::string &name, const std::string &label,
                        Task::Priority prior){
    TaskDTO task(date, name, label, prior);
    return task;
}

TaskDTO::TaskDTO(const TaskID &taskId, const Date &date, const std::string &name, const std::string &label,
        Task::Priority prior) : id_(taskId), date_(date), name_(name), label_(label), prior_(prior) {}

TaskDTO::TaskDTO(const Date &date, const std::string &name, const std::string &label,
                 Task::Priority prior) : id_(TaskID::create(0)), date_(date),
                                        name_(name), label_(label), prior_(prior) {}

const TaskID &TaskDTO::getTaskId() const {
    return id_;
}

const Date &TaskDTO::getDate() const {
    return date_;
}

const std::string &TaskDTO::getName() const {
    return name_;
}

const std::string &TaskDTO::getLabel() const {
    return label_;
}

Task::Priority TaskDTO::getPrior() const {
    return prior_;
}
