//
// Created by ilya on 31.10.2020.
//

#ifndef TODOLIST_TASKDTO_H
#define TODOLIST_TASKDTO_H

#include <iostream>
#include <string>
#include "TaskPriority.h"
#include "TaskID.h"
#include "boost/date_time/gregorian/gregorian.hpp"
/*
 * Data Transfer Object containing fields representing task.
 *
 * @author Ilya Dmitriev
 */
class TaskDTO {

public:

    static TaskDTO create(const TaskID&,
                          const boost::gregorian::date &,
                          const std::string &,
                          const std::string &,
                          TaskPriority,
                          bool);
public:

    const boost::gregorian::date &getDate() const;

    const std::string &getName() const;

    const std::string &getLabel() const;

    TaskPriority getPriority() const;

    TaskID getId() const;

    bool isCompleted() const;

private:

    TaskDTO(const TaskID &taskID,
            const boost::gregorian::date &date,
            const std::string &name,
            const std::string &label,
            TaskPriority priority,
            bool completed);

private:
    TaskID id_;
    boost::gregorian::date date_;
    std::string name_;
    std::string label_;
    TaskPriority priority_;
    bool completed_;
};

#endif //TODOLIST_TASKDTO_H
