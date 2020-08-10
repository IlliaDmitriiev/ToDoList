//
// Created by illia.dmitriiev on 7/27/2020.
//

#ifndef TODOLIST_STORAGEBYDATE_H
#define TODOLIST_STORAGEBYDATE_H

#include "StorageByPriority.h"
#include <unordered_map>

class StorageByDate {

public:
    void addTask(const std::weak_ptr<FullTask>& ft);
    void deleteTask(const std::weak_ptr<FullTask>& ft);

public:
    const std::unordered_map<Date, StorageByPriority, Date::Hasher, Date::Comparator> &getMap() const;

private:
    std::unordered_map<Date, StorageByPriority, Date::Hasher, Date::Comparator> map_;

};

#endif //TODOLIST_STORAGEBYDATE_H
