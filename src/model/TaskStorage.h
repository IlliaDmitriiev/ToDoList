//
// Created by Илля on 03.08.2020.
//

#ifndef TODOLIST_TASKSTORAGE_H
#define TODOLIST_TASKSTORAGE_H

#include "FullTask.h"
#include <unordered_map>
#include <optional>

class TaskStorage {

public:
    void addTask(std::shared_ptr<FullTask> sft);
    std::optional<std::weak_ptr<FullTask>> getTask(TaskID id);
    void deleteTask(TaskID id);


private:
    std::unordered_map<TaskID, std::shared_ptr<FullTask>,
            TaskID::Hasher, TaskID::Comparator > allTasks_;
};


#endif //TODOLIST_TASKSTORAGE_H
