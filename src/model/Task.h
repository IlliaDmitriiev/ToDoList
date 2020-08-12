//
// Created by illia.dmitriiev on 7/27/2020.
//

#ifndef TODOLIST_TASK_H
#define TODOLIST_TASK_H

#include <iostream>
#include <string>
#include <ctime>
#include "Date.h"
#include "api/TaskPriority.h"


class Task{

public:
    static Task create(const Date &date, const std::string &name, const std::string &label, TaskPriority prior){
        Task task(date, name, label, prior);
        return task;
    }

public:
    Date getDate() const {
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
                t1.getDate().getYear() == t2.getDate().getYear() &&
                t1.getDate().getMounth() == t2.getDate().getMounth() &&
                t1.getDate().getDay() == t2.getDate().getDay() &&
                t1.getName() == t2.getName() &&
                t1.getLabel() == t2.getLabel() &&
                t1.getPriority() == t2.getPriority();
    }

private:
    Task(const Date &date, const std::string &name, const std::string &label, TaskPriority priority)
            : date_(date), name_(name), label_(label), priority_(priority) {}

private:
    Date date_;
    std::string name_;
    std::string label_;
    TaskPriority priority_;
};


#endif //TODOLIST_TASK_H
