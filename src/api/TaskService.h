//
// Created by illia.dmitriiev on 7/27/2020.
//

#ifndef TODOLIST_TASKSERVICE_H
#define TODOLIST_TASKSERVICE_H


#include "FullTask.h"
#include "StorageByDate.h"
#include "IDGenerator.h"

#include <algorithm>

class TaskService {

public:
    TaskID addTask(Date date, const std::string &name, const std::string &label, Task::Priority prior);
    TaskID addSubtask(TaskID id, Date date, const std::string &name,
            const std::string &label, Task::Priority prior);
    void removeTask(TaskID id);
    void updateDataAfterPeriodOfTime();

public:
    const StorageByDate &getData() const;

private:
    IDGenerator generator;
    StorageByDate data;
    std::unordered_map<int, std::shared_ptr<FullTask> > allTasks;

};

#endif //TODOLIST_TASKSERVICE_H
