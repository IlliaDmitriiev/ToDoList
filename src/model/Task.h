//
// Created by illia.dmitriiev on 7/27/2020.
//

#ifndef TODOLIST_TASK_H
#define TODOLIST_TASK_H

#include <iostream>
#include <string>
#include <ctime>
#include "Date.h"


class Task{

public:
    enum class Priority{
        None,
        First,
        Second,
        Third
    };

public:
    static Task create(const Date &date, const std::string &name, const std::string &label, Task::Priority prior){
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

    Priority getPrior() const {
        return prior_;
}
public:
    static bool Compare(const Task &t1, const Task &t2){
        return
                t1.getDate().getYear() == t2.getDate().getYear() &&
                t1.getDate().getMounth() == t2.getDate().getMounth() &&
                t1.getDate().getDay() == t2.getDate().getDay() &&
                t1.getName() == t2.getName() &&
                t1.getLabel() == t2.getLabel() &&
                t1.getPrior() == t2.getPrior();
    }

private:
    Task(const Date &date, const std::string &name, const std::string &label, Task::Priority prior)
            : date_(date), name_(name), label_(label), prior_(prior) {}

private:
    Date date_;
    std::string name_;
    std::string label_;
    Priority prior_;
};


#endif //TODOLIST_TASK_H
