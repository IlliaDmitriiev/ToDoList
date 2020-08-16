//
// Created by illia.dmitriiev on 7/27/2020.
//

#ifndef TODOLIST_TASK_H
#define TODOLIST_TASK_H

#include <iostream>
#include <string>
#include <ctime>
#include "boost/date_time/gregorian/gregorian.hpp"
#include "api/TaskPriority.h"

/*'
 * class which holds data
 *
 * @note read only
 *
 * @author: Ilya Dmitriev
 */
class Task{

public:
    static Task create(const boost::gregorian::date &date, const std::string &name, const std::string &label, TaskPriority prior){
        Task task(date, name, label, prior);
        return task;
    }

public:
    boost::gregorian::date getDate() const {
        return date_;
    }

    const std::string &getName() const {
        return name_;
    }

    const std::string &getLabel() const {
        return label_;
    }

    TaskPriority getPriority() const {
        return priority_;
}

public:
    static bool Compare(const Task &t1, const Task &t2){
        return
                t1.getDate().year() == t2.getDate().year() &&
                t1.getDate().month() == t2.getDate().month() &&
                t1.getDate().day() == t2.getDate().day() &&
                t1.getName() == t2.getName() &&
                t1.getLabel() == t2.getLabel() &&
                t1.getPriority() == t2.getPriority();
    }

private:
    Task(const boost::gregorian::date &date, const std::string &name, const std::string &label, TaskPriority priority)
            : date_(date), name_(name), label_(label), priority_(priority) {}

private:
    boost::gregorian::date date_;
    std::string name_;
    std::string label_;
    TaskPriority priority_;
};


#endif //TODOLIST_TASK_H
