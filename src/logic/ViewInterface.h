//
// Created by Илля on 01.08.2020.
//

#ifndef TODOLIST_VIEWINTERFACE_H
#define TODOLIST_VIEWINTERFACE_H

#include "FullTask.h"
#include <map>
#include <vector>

class ViewInterface {

public:
    virtual std::vector<std::weak_ptr<FullTask>> getAllTasksByPrior() = 0;
    virtual std::vector<std::weak_ptr<FullTask>> getTasksForToday(Date date) = 0;
    virtual std::vector<std::weak_ptr<FullTask>> getTasksForWeek(Date date)= 0;

public:
    virtual void addTask(const std::weak_ptr<FullTask>& ft)= 0;
    virtual bool deleteTask(const std::weak_ptr<FullTask>& ft)= 0;

};


#endif //TODOLIST_VIEWINTERFACE_H
