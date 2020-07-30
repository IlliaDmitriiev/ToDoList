//
// Created by illia.dmitriiev on 7/27/2020.
//

#ifndef TODOLIST_STORAGEBYDATE_H
#define TODOLIST_STORAGEBYDATE_H

#include "StorageByPrior.h"


class StorageByDate {

public:

    void addTask(const FullTask& ft, Task::Priority prior, TaskID id);
    void removeTask(TaskID taskID);

    const std::unordered_map<Date, StorageByPrior, Date::Hasher, Date::Comparator> &getMp() const;

private:
    std::unordered_map<Date, StorageByPrior , Date::Hasher, Date::Comparator> mp;

};



#endif //TODOLIST_STORAGEBYDATE_H
