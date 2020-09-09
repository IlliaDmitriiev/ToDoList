//
// Created by Илля on 03.08.2020.
//

#ifndef TODOLIST_TASKSTORAGE_H
#define TODOLIST_TASKSTORAGE_H

#include "TaskStorageInterface.h"

class TaskStorage: public TaskStorageInterface{

public:
    bool addTask(std::shared_ptr<FullTask> sft) override;
    std::optional<std::weak_ptr<FullTask>> getTask(TaskID id)override;
    bool deleteSubtaskInParent(TaskID ParentID, TaskID taskID)override;
    bool deleteTask(TaskID id) override;


private:
    std::unordered_map<TaskID, std::shared_ptr<FullTask>,
            TaskID::Hasher, TaskID::Comparator > allTasks_;
};


#endif //TODOLIST_TASKSTORAGE_H
