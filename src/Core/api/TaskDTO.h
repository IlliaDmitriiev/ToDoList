//
// Created by Илля on 29.07.2020.
//

#ifndef TODOLIST_TASKDTO_H
#define TODOLIST_TASKDTO_H

#include <Core/api/TaskID.h>
#include "Core/model/Task.h"

/*
 * Data Transfer Object containing fields representing task.
 *
 * @author Ilya Dmitriev
 */
class TaskDTO {

public:
    static TaskDTO create(const TaskID &taskId, const boost::gregorian::date &date, const std::string &name, const std::string &label,
                          TaskPriority priority);
    static TaskDTO create(const boost::gregorian::date &date, const std::string &name, const std::string &label,
                                   TaskPriority priority);
public:

    const boost::gregorian::date &getDate() const;

    const std::string &getName() const;

    const std::string &getLabel() const;

    TaskPriority getPriority() const;

    const TaskID &getId() const;

    bool isCompleted() const;

private:
    TaskDTO(const TaskID &taskID, const boost::gregorian::date &date, const std::string &name, const std::string &label,
            TaskPriority priority);
    TaskDTO(const boost::gregorian::date &date, const std::string &name, const std::string &label,
            TaskPriority priority);

private:
    TaskID id_;
    boost::gregorian::date date_;
    std::string name_;
    std::string label_;
    TaskPriority priority_;
    bool completed_;
};

#endif //TODOLIST_TASKDTO_H
