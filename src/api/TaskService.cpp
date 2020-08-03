//
// Created by illia.dmitriiev on 7/27/2020.
//

#include "TaskService.h"

TaskID TaskService::addTask(Date date, const std::string &name, const std::string &label, Task::Priority prior){
    TaskID id = generator_.generateId();
    Task t = Task::create(date, name, label, prior);
    FullTask ft = FullTask::create(id, t);
    auto sft = std::make_shared<FullTask>(ft);
    view_.getViewByD().getStorage().addTask(sft);
    view_.getViewByP().getStorage().putTaskInRightPlace(sft);
    storage_.addTask(std::move(sft));
    return id;
}

TaskID TaskService::addSubtask(TaskID taskID, Date date, const std::string &name, const std::string &label, Task::Priority prior){
    TaskID subtaskID = addTask(date, name, label, prior);
    return subtaskID;
}

std::vector<TaskDTO> TaskService::getAllTasksByPrior(){
    auto v = view_.getAllTasksByPrior();
    std::vector<TaskDTO> vec;
    for(auto i: v){
        FullTask::Print(i);
        vec.push_back(convertor_.convert(i));
    }
    return vec;
}

std::vector<TaskDTO> TaskService::getTasksForToday(){
    auto v = view_.getTasksForToday();
    std::vector<TaskDTO> vec;
    for(auto i: v){
        FullTask::Print(i);
        vec.push_back(convertor_.convert(i));
    }
    return vec;
}

std::vector<TaskDTO> TaskService::getTasksForWeek(){
    auto v = view_.getTasksForWeek();
    std::vector<TaskDTO> vec;
    for(auto i: v) {
        FullTask::Print(i);
        vec.push_back(convertor_.convert(i));
    }
    return vec;
};

void TaskService::removeTask(TaskID id){
   collector_.deleteTask(storage_, id);
}

TaskDTO TaskService::getTask(TaskID id){
    FullTask::Print(storage_.getTask(id));
    return convertor_.convert(storage_.getTask(id));
}


