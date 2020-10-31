//
// Created by ilya on 31.10.2020.
//

#include "TaskDTO.h"

TaskDTO TaskDTO::create(const TaskID& id,
                        const boost::gregorian::date& date,
                        const std::string& name,
                        const std::string& label,
                        TaskPriority priority,
                        bool completed)
{
    TaskDTO task(id, date, name, label, priority, completed);
    return task;
}

TaskDTO::TaskDTO(const TaskID &taskID,
                 const boost::gregorian::date &date,
                 const std::string &name,
                 const std::string &label,
                 TaskPriority priority,
                 bool completed)
                 :
                 id_(taskID),
                 date_(date),
                 name_(name),
                 label_(label),
                 priority_(priority),
                 completed_(completed)
{

}

const boost::gregorian::date &TaskDTO::getDate() const {
    return date_;
}

const std::string& TaskDTO::getName() const {
    return name_;
}

const std::string& TaskDTO::getLabel() const {
    return label_;
}

TaskPriority TaskDTO::getPriority() const {
    return priority_;
}

TaskID TaskDTO::getId() const {
    return id_;
}

bool TaskDTO::isCompleted() const {
    return completed_;
}
