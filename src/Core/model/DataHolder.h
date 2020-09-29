//
// Created by ilya on 24.09.2020.
//

#ifndef TODOLIST_DATAHOLDER_H
#define TODOLIST_DATAHOLDER_H

#include "DataInterface.h"

class DataHolder: public DataInterface{
public:
    DataHolder( std::unique_ptr<IDGeneratorInterface> generator,
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
    AddTaskResult addTask(const ServiceTaskDTO &taskDto) override;
    AddTaskResult addSubtask(TaskID taskID, const ServiceTaskDTO &subtask) override;

    RequstTaskResult deleteTask(TaskID id) override;
    RequstTaskResult complete(TaskID id) override;
    RequstTaskResult editTask(TaskID id, const ServiceTaskDTO &subtask) override;

public:
    std::vector<ServiceTaskDTO> getSubtasks(TaskID id) override;
    std::vector<ServiceTaskDTO> getAllTasks() override;
    std::optional<ServiceTaskDTO> getTask(TaskID id) override;

    const ViewInterface& getByPriority() override;
    const ViewInterface& getByDate() override;

private:
    bool removeTask(const std::weak_ptr<FullTask> &task) override;

private:
    std::unique_ptr<IDGeneratorInterface> generator_;
    std::unique_ptr<TaskStorageInterface> storage_;
    std::unique_ptr<ViewInterface> byPriority_;
    std::unique_ptr<ViewInterface> byDate_;
};


#endif //TODOLIST_DATAHOLDER_H
