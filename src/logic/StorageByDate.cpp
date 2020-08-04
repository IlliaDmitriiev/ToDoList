//
// Created by illia.dmitriiev on 7/27/2020.
//

#include "StorageByDate.h"

void StorageByDate::addTask(const std::weak_ptr<FullTask> ft){

    Date date = ft.lock()->getTask().getDate();
    auto foundDate = map_.find(date);

    if (foundDate != map_.end()) {
        foundDate->second.putTaskInRightPlace(ft);
    }
    else {
        StorageByPrior v;
        v.putTaskInRightPlace(ft);
        map_.insert({date, v});
    }
}

void StorageByDate::deleteDanglingPointers(){
    for (auto &i: map_){
        i.second.deleteDanglingPointers();
    }
}

const std::unordered_map<Date, StorageByPrior, Date::Hasher, Date::Comparator> &StorageByDate::getMap() const {
    return map_;
}


