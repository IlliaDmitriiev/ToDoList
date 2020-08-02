//
// Created by illia.dmitriiev on 7/27/2020.
//

#ifndef TODOLIST_TASKSERVICE_H
#define TODOLIST_TASKSERVICE_H


#include "FullTask.h"
#include "StorageByDate.h"
#include "IDGenerator.h"
#include "View.h"
#include "Convertor.h"

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
    void updateDataAfterPeriodOfTime();

private:
    IDGenerator generator_;
    View view_;
    Convertor convertor;

private:
    std::unordered_map<TaskID, std::shared_ptr<FullTask>, TaskID::Hasher, TaskID::Comparator > allTasks;

};

#endif //TODOLIST_TASKSERVICE_H
