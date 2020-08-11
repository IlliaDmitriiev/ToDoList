//
// Created by Илля on 30.07.2020.
//

#ifndef TODOLIST_VIEWBYPRIORITY_H
#define TODOLIST_VIEWBYPRIORITY_H

#include "ViewByPriority.h"


class ViewByDate {

public:
    std::vector<std::weak_ptr<FullTask>> getTasksForToday(Date date);
    std::vector<std::weak_ptr<FullTask>> getTasksForWeek(Date date);

public:
    void addTask(const std::weak_ptr<FullTask>& ft);
    void deleteTask(const std::weak_ptr<FullTask>& ft);

private:
    std::unordered_map<Date, ViewByPriority, Date::Hasher, Date::Comparator> map_;
};


#endif //TODOLIST_VIEWBYPRIORITY_H
