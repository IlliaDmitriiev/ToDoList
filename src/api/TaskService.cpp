//
// Created by illia.dmitriiev on 7/27/2020.
//

#include "TaskService.h"

TaskID TaskService::addTask(Date date, const std::string &name, const std::string &label, Task::Priority prior){
    TaskID taskId = generator.generateId();
    Task t = Task::create(date, name, label, prior);
    FullTask ft = FullTask::create(generator, t);
    data.addTask(ft, prior, taskId);
    return taskId;
}

TaskID TaskService::addSubtask(TaskID taskID, Date date, const std::string &name, const std::string &label, Task::Priority prior){
    TaskID subtaskID = addTask(date, name, label, prior);
    data.addSubtask(taskID, subtaskID);
    return subtaskID;
}

void TaskService::removeTask(TaskID taskID){
    data.removeTask(taskID);
}

void TaskService::updateDataAfterPeriodOfTime(){
    auto d = data.getVByPriors();
    d.updateVectors();
}

const DataMapsLogic &TaskService::getData() const {
    return data;
}