//
// Created by Илля on 01.08.2020.
//

#ifndef TODOLIST_VIEWINTERFACE_H
#define TODOLIST_VIEWINTERFACE_H

#include "model/FullTask.h"
#include <map>
#include <vector>

class ViewInterface {

public:
    virtual std::vector<std::weak_ptr<FullTask>> getAllTasksByPrior() = 0;
    virtual std::vector<std::weak_ptr<FullTask>> getTasksForToday(boost::gregorian::date date) = 0;
    virtual std::vector<std::weak_ptr<FullTask>> getTasksForWeek(boost::gregorian::date date)= 0;

public:
    virtual bool addTask(const std::weak_ptr<FullTask>& ft)= 0;
    virtual bool deleteTask(const std::weak_ptr<FullTask>& ft)= 0;
    virtual ~ViewInterface() = default;
};


#endif //TODOLIST_VIEWINTERFACE_H
