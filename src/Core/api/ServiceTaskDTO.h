//
// Created by Илля on 29.07.2020.
//

#ifndef TODOLIST_SERVICETASKDTO_H
#define TODOLIST_SERVICETASKDTO_H

#include <Core/api/TaskID.h>
#include "Core/model/Task.h"

/*
 * Data Transfer Object containing fields representing task.
 *
 * @author Ilya Dmitriev
 */
class ServiceTaskDTO {

public:
    static ServiceTaskDTO create(const TaskID &,
                                 const boost::gregorian::date &,
                                 const std::string &,
                                 const std::string &,
                                 TaskPriority );

    static ServiceTaskDTO create(const boost::gregorian::date &,
                                 const std::string &,
                                 const std::string &,
                                 TaskPriority);

    static ServiceTaskDTO create(const TaskID&,
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

    const TaskID &getId() const;

    bool isCompleted() const;

private:
    ServiceTaskDTO(const TaskID &taskID,
                   const boost::gregorian::date &date,
                   const std::string &name,
                   const std::string &label,
                   TaskPriority priority);

    ServiceTaskDTO(const boost::gregorian::date &date,
                   const std::string &name,
                   const std::string &label,
                   TaskPriority priority);

    ServiceTaskDTO(const TaskID &taskID,
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

#endif //TODOLIST_SERVICETASKDTO_H
