//
// Created by Илля on 03.08.2020.
//

#include "TaskStorage.h"

bool TaskStorage::addTask(std::shared_ptr<FullTask> sft){
    allTasks_.insert({sft->getId(), std::move(sft)});
}

std::optional<std::weak_ptr<FullTask>> TaskStorage::getTask(TaskID id){
    if (allTasks_.find(id) == allTasks_.end())
        return std::nullopt;
    else
        return allTasks_[id];
}


bool TaskStorage::deleteSubtaskInParent(TaskID ParentID, TaskID taskID){
    auto task = allTasks_.find(taskID);
    auto ParentTask = allTasks_.find(ParentID);

    if(ParentTask == allTasks_.end()|| task ==allTasks_.end())
        return false;

    if (ParentID.getId()!=taskID.getId())
        ParentTask->second->deleteSubtask(taskID);

    return true;
}

bool TaskStorage::deleteTask(TaskID id){
    return allTasks_.erase(id);
}


