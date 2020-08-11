//
// Created by Илля on 31.07.2020.
//

#ifndef TODOLIST_PRIORITYVIEW_H
#define TODOLIST_PRIORITYVIEW_H

#include "FullTask.h"
#include <map>
#include <vector>

class ViewByPriority {

public:
    std::vector<std::weak_ptr<FullTask>> getAllTasks();

public:
    void addTask(std::weak_ptr<FullTask> cur);
    void deleteTask(Task::Priority priority, TaskID id);

public:
    const std::map<Task::Priority, std::map<TaskID, std::weak_ptr<FullTask>, TaskID::MapComparator>> &getMap() const;

private:
    std::map<Task::Priority, std::map<TaskID, std::weak_ptr<FullTask>, TaskID::MapComparator> > map_;

};

#endif //TODOLIST_PRIORITYVIEW_H
