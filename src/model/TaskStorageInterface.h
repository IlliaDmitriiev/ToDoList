//
// Created by illia on 14.08.20.
//

#ifndef TODOLIST_TASKSTORAGEINTERFACE_H
#define TODOLIST_TASKSTORAGEINTERFACE_H

#include "FullTask.h"
#include <unordered_map>
#include <vector>
#include <optional>

class TaskStorageInterface {

public:
    virtual bool addTask(std::shared_ptr<FullTask> sft) = 0;
    virtual std::optional<std::weak_ptr<FullTask>> getTask(TaskID id)= 0;
    virtual bool deleteSubtaskInParent(TaskID ParentID, TaskID taskID)= 0;
    virtual bool deleteTask(TaskID id)= 0;

};

#endif //TODOLIST_TASKSTORAGEINTERFACE_H
