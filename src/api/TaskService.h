//
// Created by illia.dmitriiev on 7/27/2020.
//

#ifndef TODOLIST_TASKSERVICE_H
#define TODOLIST_TASKSERVICE_H


#include "logic/FullTask.h"
#include "logic/StorageByDate.h"
#include "logic/IDGenerator.h"
#include "logic/View.h"
#include "logic/Convertor.h"
#include "logic/Cleaner.h"
#include "logic/StorageForSharedPtr.h"

#include <algorithm>

class TaskService {

public:
    TaskID addTask(Date date, const std::string &name,
            const std::string &label, Task::Priority prior);
    TaskID addSubtask(TaskID id, Date date, const std::string &name,
            const std::string &label, Task::Priority prior);
public:
    std::vector<TaskDTO> getAllTasksByPrior();
    std::vector<TaskDTO> getTasksForToday();
    std::vector<TaskDTO> getTasksForWeek();

public:
    void removeTask(TaskID id);
    TaskDTO getTask(TaskID id);

private:
    IDGenerator generator_;
    View view_;
    Convertor convertor_;
    StorageForSharedPtr storage_;
    Cleaner cleaner_;

};

#endif //TODOLIST_TASKSERVICE_H
