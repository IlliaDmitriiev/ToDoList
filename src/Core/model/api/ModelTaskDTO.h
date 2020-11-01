//
// Created by ilya on 30.09.2020.
//

#ifndef TODOLIST_MODELTASKDTO_H
#define TODOLIST_MODELTASKDTO_H

#include <Core/api/TaskID.h>
#include "Core/model/Task.h"

/*
 * Data Transfer Object containing fields representing task.
 *
 * @author Ilya Dmitriev
 */
class ModelTaskDTO {

public:
    static ModelTaskDTO create(const TaskID &taskID,
                               const boost::gregorian::date &date,
                               const std::string &name,
                               const std::string &label,
                               TaskPriority priority,
                               bool isCompleted
    );

    static ModelTaskDTO create(const TaskID &taskID,
                               const boost::gregorian::date &date,
                               const std::string &name,
                               const std::string &label,
                               TaskPriority priority);

    static ModelTaskDTO create(const boost::gregorian::date &date,
                               const std::string &name,
                               const std::string &label,
                               TaskPriority priority);

public:

    const boost::gregorian::date &getDate() const;

    const std::string &getName() const;

    const std::string &getLabel() const;

    TaskPriority getPriority() const;

    const TaskID &getId() const;

    bool isCompleted() const;


private:
    ModelTaskDTO(const TaskID &id,
                 const boost::gregorian::date &date,
                 const std::string &name,
                 const std::string &label,
                 TaskPriority priority);

    ModelTaskDTO(const TaskID &id,
                 const boost::gregorian::date &date,
                 const std::string &name,
                 const std::string &label,
                 TaskPriority priority,
                 bool completed);

    ModelTaskDTO(const boost::gregorian::date &date,
                 const std::string &name,
                 const std::string &label,
                 TaskPriority priority);


private:
    TaskID id_;
    boost::gregorian::date date_;
    std::string name_;
    std::string label_;
    TaskPriority priority_;
    bool completed_;
};

#endif //TODOLIST_MODELTASKDTO_H
