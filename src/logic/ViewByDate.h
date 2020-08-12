//
// Created by Илля on 30.07.2020.
//

#ifndef TODOLIST_VIEWBYPRIORITY_H
#define TODOLIST_VIEWBYPRIORITY_H

#include "ViewInterface.h"


class ViewByDate: public ViewInterface {

public:
    std::vector<std::weak_ptr<FullTask>> getAllTasksByPrior() override;
    std::vector<std::weak_ptr<FullTask>> getTasksForToday(Date date) override ;
    std::vector<std::weak_ptr<FullTask>> getTasksForWeek(Date date) override ;

public:
    void addTask(const std::weak_ptr<FullTask>& ft)  override ;
    bool deleteTask(const std::weak_ptr<FullTask>& ft) override ;

private:
    std::unordered_map<Date,
        std::map<TaskPriority,
            std::map<TaskID, std::weak_ptr<FullTask>, TaskID::MapComparator> >,
        Date::Hasher,
        Date::Comparator> map_;
};


#endif //TODOLIST_VIEWBYPRIORITY_H
