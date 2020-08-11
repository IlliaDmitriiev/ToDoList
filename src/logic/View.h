//
// Created by Илля on 01.08.2020.
//

#ifndef TODOLIST_VIEW_H
#define TODOLIST_VIEW_H


#include "ViewByDate.h"
#include "ViewByPriority.h"

class View {

public:
    std::vector<std::weak_ptr<FullTask>> getAllTasksByPrior();
    std::vector<std::weak_ptr<FullTask>> getTasksForToday();
    std::vector<std::weak_ptr<FullTask>> getTasksForWeek();

public:
    void addTask(const std::weak_ptr<FullTask>& ft);
    void deleteTask(const std::weak_ptr<FullTask>& ft);

private:
    ViewByDate viewByD_;
    ViewByPriority viewByP_;
};


#endif //TODOLIST_VIEW_H
