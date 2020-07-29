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
    static Task create(Date date, const std::string &name, const std::string &label, Task::Priority prior){
        Task t(date, name, label, prior);
        return t;
    }

public:
    Date getDate() const {
        return date;
    }

    const std::string &getName() const {
        return name;
    }

    const std::string &getLabel() const {
        return label;
    }

    Priority getPrior() const {
        return prior;
    }

private:
    Task(Date date, const std::string &name, const std::string &label, Task::Priority prior)
            : date(date), name(name), label(label), prior(prior) {}

private:
    Date date;
    std::string name;
    std::string label;
    Priority prior;
};


#endif //TODOLIST_TASK_H
