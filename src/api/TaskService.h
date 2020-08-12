//
// Created by illia.dmitriiev on 7/27/2020.
//

#ifndef TODOLIST_TASKSERVICE_H
#define TODOLIST_TASKSERVICE_H


#include "model/FullTask.h"
#include "logic/IDGenerator.h"
#include "logic/ViewInterface.h"
#include "logic/ViewByPriority.h"
#include "logic/ViewByDate.h"
#include "logic/TaskConvertor.h"
#include "model/TaskStorage.h"
#include "TaskCreationResult.h"
#include <algorithm>

class TaskService {

public:
    TaskService(
        std::unique_ptr<ViewInterface> byPriority,
        std::unique_ptr<ViewInterface> byDate)
    :
    generator_(),
    storage_(),
    byPriority_(std::move(byPriority)),
    byDate_(std::move(byDate))
    {}

public:
    TaskCreationResult addTask(const TaskDTO &taskDto);
    TaskCreationResult addSubtask(TaskID taskID, const TaskDTO &subTask);

public:
    std::vector<TaskDTO> getAllTasksByPriority();
    std::vector<TaskDTO> getTasksForToday();
    std::vector<TaskDTO> getTasksForWeek();

public:
    void removeTask(TaskID id);
    std::optional<TaskDTO> getTask(TaskID id);

private:
    IDGenerator generator_;
    TaskStorage storage_;

private:
    std::unique_ptr<ViewInterface> byPriority_;
    std::unique_ptr<ViewInterface> byDate_;
};

#endif //TODOLIST_TASKSERVICE_H
