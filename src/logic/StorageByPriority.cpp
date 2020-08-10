//
// Created by illia.dmitriiev on 7/27/2020.
//

#include "StorageByPriority.h"

void StorageByPriority::addTask(std::weak_ptr<FullTask> cur){
    Task::Priority priority = cur.lock()->getTask().getPrior();
    map_[(int)priority][cur.lock()->getId()] = cur;

}

void StorageByPriority::deleteTask(Task::Priority priority, TaskID id){
    map_[(int)priority].erase(id);
}

const std::map<int, std::map<TaskID, std::weak_ptr<FullTask>, TaskID::MapComparator>> &StorageByPriority::getMap() const {
    return map_;
}
