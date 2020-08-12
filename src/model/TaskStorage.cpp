//
// Created by Илля on 03.08.2020.
//

#include "TaskStorage.h"

void TaskStorage::addTask(std::shared_ptr<FullTask> sft){
    allTasks_.insert({sft->getId(), std::move(sft)});
}

std::optional<std::weak_ptr<FullTask>> TaskStorage::getTask(TaskID id){
    if (allTasks_.find(id) == allTasks_.end())
        return std::nullopt;
    else
        return allTasks_[id];
}

void TaskStorage::deleteTask(TaskID id){
    allTasks_.erase(id);
}

