//
// Created by Илля on 03.08.2020.
//

#ifndef TODOLIST_STORAGEFORSHAREDPTR_H
#define TODOLIST_STORAGEFORSHAREDPTR_H

#include "FullTask.h"
#include <unordered_map>
#include <optional>

class StorageForSharedPtr {

public:
    void addTask(std::shared_ptr<FullTask> sft);
    std::optional<std::weak_ptr<FullTask>> getTask(TaskID id);
    void deleteTask(TaskID id);


private:
    std::unordered_map<TaskID, std::shared_ptr<FullTask>,
            TaskID::Hasher, TaskID::Comparator > allTasks_;
};


#endif //TODOLIST_STORAGEFORSHAREDPTR_H
