//
// Created by ilya on 30.09.2020.
//

#include "ModelTaskDTO.h"

ModelTaskDTO ModelTaskDTO::create(const TaskID &taskID,
                                  const boost::gregorian::date &date,
                                  const std::string &name,
                                  const std::string &label,
                                  TaskPriority priority,
                                  bool isCompleted)
{
    ModelTaskDTO task(taskID, date, name, label, priority, isCompleted);
    return task;
}

ModelTaskDTO ModelTaskDTO::create(const TaskID &taskID,
                                  const boost::gregorian::date &date,
                                  const std::string &name,
                                  const std::string &label,
                                  TaskPriority priority)
{
    ModelTaskDTO task(taskID, date, name, label, priority);
    return task;
}

ModelTaskDTO ModelTaskDTO::create(const boost::gregorian::date &date,
                                  const std::string &name,
                                  const std::string &label,
                                  TaskPriority priority)
{
    ModelTaskDTO task(date, name, label, priority);
    return task;
}

const boost::gregorian::date &ModelTaskDTO::getDate() const {
    return date_;
}

const std::string &ModelTaskDTO::getName() const {
    return name_;
}

const std::string &ModelTaskDTO::getLabel() const {
    return label_;
}

TaskPriority ModelTaskDTO::getPriority() const {
    return priority_;
}

const TaskID &ModelTaskDTO::getId() const {
    return id_;
}

bool ModelTaskDTO::isCompleted() const {
    return completed_;
}

ModelTaskDTO::ModelTaskDTO(const TaskID &id,
                           const boost::gregorian::date &date,
                           const std::string &name,
                           const std::string &label,
                           TaskPriority priority,
                           bool completed)
        :
        id_(id),
        date_(date),
        name_(name),
        label_(label),
        priority_(priority),
        completed_(completed)
{

}

ModelTaskDTO::ModelTaskDTO(const TaskID &id,
                           const boost::gregorian::date &date,
                           const std::string &name,
                           const std::string &label,
                           TaskPriority priority)
        :
        id_(id),
        date_(date),
        name_(name),
        label_(label),
        priority_(priority),
        completed_(false)
{

}

ModelTaskDTO::ModelTaskDTO(const boost::gregorian::date &date,
                           const std::string &name,
                           const std::string &label,
                           TaskPriority priority)
        :
        id_(TaskID::create(0)),
        date_(date),
        name_(name),
        label_(label),
        priority_(priority),
        completed_(false)
{

}
