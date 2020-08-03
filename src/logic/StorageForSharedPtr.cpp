//
// Created by Илля on 03.08.2020.
//

#include "StorageForSharedPtr.h"

void StorageForSharedPtr::addTask(TaskID id, std::shared_ptr<FullTask> sft){
    allTasks_.insert({id, std::move(sft)});
}

std::weak_ptr<FullTask> StorageForSharedPtr::getTask(TaskID id){
    return allTasks_[id];
}

void StorageForSharedPtr::deleteTask(TaskID id){
    allTasks_.erase(id);
}

const std::unordered_map<TaskID, std::shared_ptr<FullTask>, TaskID::Hasher,
TaskID::Comparator> &StorageForSharedPtr::getAllTasks() const {
    return allTasks_;
}
