//
// Created by illia.dmitriiev on 7/27/2020.
//

#include "TaskService.h"

TaskID TaskService::addTask(Date date, const std::string &name, const std::string &label, Task::Priority prior){
    TaskID id = generator_.generateId();
    Task t = Task::create(date, name, label, prior);
    FullTask ft = FullTask::create(generator_, t);
    auto sft = std::make_shared<FullTask>(ft);
    view_.getViewByD().getStorage().addTask(sft);
    view_.getViewByP().getStorage().putTaskInRightPlace(sft);
    allTasks.insert({id, std::move(sft)});
    return id;
}

TaskID TaskService::addSubtask(TaskID taskID, Date date, const std::string &name, const std::string &label, Task::Priority prior){
    TaskID subtaskID = addTask(date, name, label, prior);
    return subtaskID;
}

void TaskService::showAllTasksByPrior(){
    auto v = view_.getAllTasksByPrior();
    for(auto i: v)
        FullTask::Print(i);
}

void TaskService::showTasksForToday(){
    auto v = view_.getTasksForToday();
    for(auto i: v)
        FullTask::Print(i);
}

void TaskService::showTasksForWeek(){
    auto v = view_.getTasksForWeek();
    for(auto i: v)
        FullTask::Print(i);
};

void TaskService::removeTask(TaskID taskID){
   // data.removeTask(taskID);
}

void TaskService::updateDataAfterPeriodOfTime(){
 //   auto d = data.getVByPriors();
   // d.updateVectors();
}
