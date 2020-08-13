//
// Created by Илля on 31.07.2020.
//

#ifndef TODOLIST_PRIORITYVIEW_H
#define TODOLIST_PRIORITYVIEW_H

#include "ViewInterface.h"

class ViewByPriority: public ViewInterface{

public:
    ViewByPriority();

public:
    std::vector<std::weak_ptr<FullTask>> getAllTasksByPrior() override;
    std::vector<std::weak_ptr<FullTask>> getTasksForToday(Date date) override;
    std::vector<std::weak_ptr<FullTask>> getTasksForWeek(Date date) override;

public:
    bool addTask(const std::weak_ptr<FullTask>& ft) override ;
    bool deleteTask(const std::weak_ptr<FullTask>& ft) override ;

private:
    std::map<TaskPriority, std::map<TaskID, std::weak_ptr<FullTask>, TaskID::MapComparator> > map_;

};

#endif //TODOLIST_PRIORITYVIEW_H
