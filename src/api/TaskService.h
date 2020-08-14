//
// Created by illia.dmitriiev on 7/27/2020.
//

#ifndef TODOLIST_TASKSERVICE_H
#define TODOLIST_TASKSERVICE_H

#include "logic/IDGenerator.h"
#include "logic/ViewInterface.h"
#include "logic/ViewByPriority.h"
#include "logic/ViewByDate.h"
#include "logic/TaskConvertor.h"
#include "model/TaskStorage.h"
#include "ReturnType.h"

class TaskService {

public:
    TaskService(
        std::unique_ptr<ViewInterface> byPriority,
        std::unique_ptr<ViewInterface> byDate)
    :
    byPriority_(std::move(byPriority)),
    byDate_(std::move(byDate))
    {}

public:
    AddTaskResult addTask(const TaskDTO &taskDto);
    AddTaskResult addSubtask(TaskID taskID, const TaskDTO &subtask);
    RequstTaskResult deleteTask(TaskID id);
    RequstTaskResult complete(TaskID id);
    RequstTaskResult postponeTask(TaskID id, boost::gregorian::date new_date);

public:
    std::vector<TaskDTO> getAllTasksByPriority();
    std::vector<TaskDTO> getTasksForToday();
    std::vector<TaskDTO> getTasksForWeek();
    std::optional<TaskDTO> getTask(TaskID id);

private:
    bool removeTask(const std::weak_ptr<FullTask> &task);

private:
    IDGenerator generator_;
    TaskStorage storage_;

private:
    std::unique_ptr<ViewInterface> byPriority_;
    std::unique_ptr<ViewInterface> byDate_;
};

#endif //TODOLIST_TASKSERVICE_H
