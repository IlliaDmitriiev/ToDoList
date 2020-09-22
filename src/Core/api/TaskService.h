//
// Created by illia.dmitriiev on 7/27/2020.
//

#ifndef TODOLIST_TASKSERVICE_H
#define TODOLIST_TASKSERVICE_H

#include "TaskServiceInterface.h"

class TaskService: public TaskServiceInterface {

public:
    TaskService(
        std::unique_ptr<IDGeneratorInterface> generator,
        std::unique_ptr<ViewInterface> byPriority,
        std::unique_ptr<ViewInterface> byDate,
        std::unique_ptr<TaskStorageInterface> storage)
    :
    generator_(std::move(generator)),
    byPriority_(std::move(byPriority)),
    byDate_(std::move(byDate)),
    storage_(std::move(storage))
    {}

public:

    AddTaskResult addTask(const TaskDTO &taskDto) override;

    AddTaskResult addSubtask(TaskID taskID, const TaskDTO &subtask) override;

    RequstTaskResult deleteTask(TaskID id) override;

    RequstTaskResult complete(TaskID id) override;

    RequstTaskResult postponeTask(TaskID id, boost::gregorian::date new_date) override;

    RequstTaskResult editTask(TaskID id, const TaskDTO &subtask) override;

public:
    std::vector<TaskDTO> getSubtasks(TaskID id) override;

    std::vector<TaskDTO> getAllTasksByPriority() override;

    std::vector<TaskDTO> getTasksForToday() override;

    std::vector<TaskDTO> getTasksForWeek() override;

    std::optional<TaskDTO> getTask(TaskID id) override;

private:

    bool removeTask(const std::weak_ptr<FullTask> &task) override;

private:
    std::unique_ptr<IDGeneratorInterface> generator_;
    std::unique_ptr<TaskStorageInterface> storage_;
    std::unique_ptr<ViewInterface> byPriority_;
    std::unique_ptr<ViewInterface> byDate_;
};

#endif //TODOLIST_TASKSERVICE_H
