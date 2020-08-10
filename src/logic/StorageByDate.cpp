//
// Created by illia.dmitriiev on 7/27/2020.
//

#include "StorageByDate.h"

void StorageByDate::addTask(const std::weak_ptr<FullTask>& ft){
    Date date = ft.lock()->getTask().getDate();
    auto foundDate = map_.find(date);

    if (foundDate != map_.end()) {
        foundDate->second.addTask(ft);
    }
    else {
        StorageByPriority map;
        map.addTask(ft);
        map_.insert({date, map});
    }
}

void StorageByDate::deleteTask(const std::weak_ptr<FullTask>& ft){
    map_[ft.lock()->getTask().getDate()].deleteTask(ft.lock()->getTask().getPrior(), ft.lock()->getId());

}

const std::unordered_map<Date, StorageByPriority, Date::Hasher, Date::Comparator> &StorageByDate::getMap() const {
    return map_;
}


