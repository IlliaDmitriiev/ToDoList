//
// Created by illia.dmitriiev on 7/27/2020.
//

#ifndef TODOLIST_TASKSERVICE_H
#define TODOLIST_TASKSERVICE_H

#include "TaskServiceInterface.h"
#include "fstream"

class TaskService: public TaskServiceInterface {

public:
    explicit TaskService(std::unique_ptr<DataInterface> model)
    :
    model_(std::move(model))
    {}

public:

    AddTaskResult addTask(const ServiceTaskDTO &taskDto) override;

    AddTaskResult addSubtask(TaskID taskID, const ServiceTaskDTO &subtask) override;

    RequstTaskResult deleteTask(TaskID id) override;

    RequstTaskResult complete(TaskID id) override;

    RequstTaskResult postponeTask(TaskID id, boost::gregorian::date new_date) override;

    RequstTaskResult editTask(TaskID id, const ServiceTaskDTO &subtask) override;

public:
    std::vector<ServiceTaskDTO> getSubtasks(TaskID id) override;

    std::vector<ServiceTaskDTO> getAllTasksByPriority() override;

    std::vector<ServiceTaskDTO> getTasksForToday() override;

    std::vector<ServiceTaskDTO> getTasksForWeek() override;

    std::optional<ServiceTaskDTO> getTask(TaskID id) override;

public:
    RequstTaskResult save(const std::string&) override;

    RequstTaskResult load(const std::string&) override;

private:
    std::unique_ptr<DataInterface> model_;

};

#endif //TODOLIST_TASKSERVICE_H
