//
// Created by illia.dmitriiev on 7/27/2020.
//

#ifndef TODOLIST_STORAGEBYPRIORITY_H
#define TODOLIST_STORAGEBYPRIORITY_H

#include "FullTask.h"
#include <vector>
#include <map>

class StorageByPriority {

public:
    void addTask(std::weak_ptr<FullTask> cur);
    void deleteTask(Task::Priority priority, TaskID id);

public:
    const std::map<int, std::map<TaskID, std::weak_ptr<FullTask>, TaskID::MapComparator>> &getMap() const;

private:

    std::map<int, std::map<TaskID, std::weak_ptr<FullTask>, TaskID::MapComparator> > map_;
};

#endif //TESTP_STORAGEBYPRIOR_H
