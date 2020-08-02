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
    allTasks.insert({id, std::move(sft)});
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
        vec.push_back(convertor.convert(i));
    }
    return vec;
}

std::vector<TaskDTO> TaskService::getTasksForToday(){
    auto v = view_.getTasksForToday();
    std::vector<TaskDTO> vec;
    for(auto i: v){
        FullTask::Print(i);
        vec.push_back(convertor.convert(i));
    }
    return vec;
}

std::vector<TaskDTO> TaskService::getTasksForWeek(){
    auto v = view_.getTasksForWeek();
    std::vector<TaskDTO> vec;
    for(auto i: v) {
        FullTask::Print(i);
        vec.push_back(convertor.convert(i));
    }
    return vec;
};

void TaskService::removeTask(TaskID taskID){
   // data.removeTask(taskID);
}

TaskDTO TaskService::getTask(TaskID id){
    return convertor.convert(allTasks[id]);
}

void TaskService::updateDataAfterPeriodOfTime(){
 //   auto d = data.getVByPriors();
   // d.updateVectors();
}
