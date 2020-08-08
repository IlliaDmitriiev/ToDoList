//
// Created by illia.dmitriiev on 7/27/2020.
//

#include "TaskService.h"

TaskCreationResult TaskService::addTask(Date date, const std::string &name, const std::string &label, Task::Priority prior){
    TaskID id = generator_.generateId();
    auto sft = std::make_shared<FullTask>(FullTask::create(id, Task::create(date, name, label, prior)));
    view_.getViewByD().getStorage().addTask(sft);
    view_.getViewByP().getStorage().putTaskInRightPlace(sft);
    storage_.addTask(std::move(sft));
    return TaskCreationResult::success(id);
}

TaskCreationResult TaskService::addSubtask(TaskID id, Date date, const std::string &name, const std::string &label, Task::Priority prior){
    auto subtaskID = addTask(date, name, label, prior);
    std::optional<std::weak_ptr<FullTask>> ft = storage_.getTask(id);
    if(ft.has_value()) {
        if (subtaskID.getTaskID().has_value()) {
            ft.value().lock()->addSubtask(storage_.getTask(subtaskID.getTaskID().value()).value());
            return TaskCreationResult::success(subtaskID.getTaskID().value());
        }
        else
            return TaskCreationResult::error("can't create subtask");
    }
    else
        return TaskCreationResult::taskNotFound();
}

std::vector<TaskDTO> TaskService::getAllTasksByPrior(){
    auto v = view_.getAllTasksByPrior();
    std::vector<TaskDTO> vec;
    for(auto i: v)
        vec.push_back(convertor_.convert(i));

    return vec;
}

std::vector<TaskDTO> TaskService::getTasksForToday(){
    auto v = view_.getTasksForToday();
    std::vector<TaskDTO> vec;
    for(auto i: v)
        vec.push_back(convertor_.convert(i));

    return vec;
}

std::vector<TaskDTO> TaskService::getTasksForWeek(){
    auto v = view_.getTasksForWeek();
    std::vector<TaskDTO> vec;
    for(auto i: v)
        vec.push_back(convertor_.convert(i));

    return vec;
};

void TaskService::removeTask(TaskID id){
   cleaner_.deleteTask(storage_, id);
}

std::optional<TaskDTO> TaskService::getTask(TaskID id){
    std::optional<std::weak_ptr<FullTask>> ft = storage_.getTask(id);
    if (ft.has_value())
        return
            std::optional<TaskDTO>(convertor_.convert(ft.value()));
     else
         return std::nullopt;
}


