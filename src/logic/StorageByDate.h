//
// Created by illia.dmitriiev on 7/27/2020.
//

#ifndef TODOLIST_STORAGEBYDATE_H
#define TODOLIST_STORAGEBYDATE_H

#include "StorageByPrior.h"
#include <unordered_map>


class StorageByDate {

public:
    void addTask(const std::weak_ptr<FullTask> ft);
    void deleteDanglingPointers();

public:
    const std::unordered_map<Date, StorageByPrior, Date::Hasher, Date::Comparator> &getMap() const;

private:
    std::unordered_map<Date, StorageByPrior , Date::Hasher, Date::Comparator> map_;

};



#endif //TODOLIST_STORAGEBYDATE_H
