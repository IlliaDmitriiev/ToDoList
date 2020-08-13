//
// Created by Илля on 03.08.2020.
//

#ifndef TODOLIST_TASKSTORAGE_H
#define TODOLIST_TASKSTORAGE_H

#include "FullTask.h"
#include <unordered_map>
#include <vector>
#include <optional>

class TaskStorage {

public:
    bool addTask(std::shared_ptr<FullTask> sft);
    std::optional<std::weak_ptr<FullTask>> getTask(TaskID id);
    bool deleteSubtaskInParent(TaskID ParentID, TaskID taskID);
    bool deleteTask(TaskID id);


private:
    std::unordered_map<TaskID, std::shared_ptr<FullTask>,
            TaskID::Hasher, TaskID::Comparator > allTasks_;
};


#endif //TODOLIST_TASKSTORAGE_H
