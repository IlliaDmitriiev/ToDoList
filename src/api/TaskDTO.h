//
// Created by Илля on 29.07.2020.
//

#ifndef TODOLIST_TASKDTO_H
#define TODOLIST_TASKDTO_H

#include <api/TaskID.h>
#include "model/Task.h"

class TaskDTO {

public:
    static TaskDTO create(const TaskID &taskId, const BoostDate &date, const std::string &name, const std::string &label,
                          TaskPriority priority);
    static TaskDTO create(const BoostDate &date, const std::string &name, const std::string &label,
                                   TaskPriority priority);
public:

    const BoostDate &getDate() const;

    const std::string &getName() const;

    const std::string &getLabel() const;

    TaskPriority getPriority() const;

    const TaskID &getId() const;

    bool isCompleted() const;

private:
    TaskDTO(const TaskID &taskID, const BoostDate &date, const std::string &name, const std::string &label,
            TaskPriority priority);
    TaskDTO(const BoostDate &date, const std::string &name, const std::string &label,
            TaskPriority priority);

private:
    TaskID id_;
    BoostDate date_;
    std::string name_;
    std::string label_;
    TaskPriority priority_;
    bool completed_;
};

#endif //TODOLIST_TASKDTO_H
