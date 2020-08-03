//
// Created by Илля on 03.08.2020.
//

#include "StorageForSharedPtr.h"

void StorageForSharedPtr::addTask(std::shared_ptr<FullTask> sft){
    allTasks_.insert({sft->getId(), std::move(sft)});
}

std::weak_ptr<FullTask> StorageForSharedPtr::getTask(TaskID id){
    if (allTasks_.find(id) == allTasks_.end())
        throw std::runtime_error("");
    else return allTasks_[id];
}

void StorageForSharedPtr::deleteTask(TaskID id){
    allTasks_.erase(id);
}

