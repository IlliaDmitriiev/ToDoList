//
// Created by Илля on 29.07.2020.
//

#ifndef TODOLIST_TASKDTO_H
#define TODOLIST_TASKDTO_H

#include <model/TaskID.h>
#include "model/Task.h"

class TaskDTO {
public:
    static TaskDTO create(const TaskID &taskId, const Date &date, const std::string &name, const std::string &label,
                          Task::Priority prior);

    const TaskID &getTaskId() const;

    const Date &getDate() const;

    const std::string &getName() const;

    const std::string &getLabel() const;

    Task::Priority getPrior() const;

private:
    TaskDTO(const TaskID &taskId, const Date &date, const std::string &name, const std::string &label,
            Task::Priority prior);

private:
    TaskID id_;
    Date date_;
    std::string name_;
    std::string label_;
    Task::Priority prior_;
};


#endif //TODOLIST_TASKDTO_H
