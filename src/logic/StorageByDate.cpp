//
// Created by illia.dmitriiev on 7/27/2020.
//

#include "StorageByDate.h"

void StorageByDate::addTask(const std::weak_ptr<FullTask> ft, Task::Priority prior){

    Date date = ft.lock()->getTask().getDate();
    auto foundDate = mp.find(date);

    if (foundDate != mp.end()) {
        foundDate->second.putTaskInRightPlace(ft, prior);
    }
    else {
        StorageByPrior v;
        v.putTaskInRightPlace(ft, prior);
        mp.insert({date, v});
    }
}

const std::unordered_map<Date, StorageByPrior, Date::Hasher, Date::Comparator> &StorageByDate::getMp() const {
    return mp;
}


