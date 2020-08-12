//
// Created by illia.dmitriiev on 7/27/2020.
//

#include "TaskService.h"

TaskCreationResult TaskService::addTask(const TaskDTO &taskDto){
    TaskID id = generator_.generateId();
    auto sft = std::make_shared<FullTask>(FullTask::create(id, TaskConvertor::transferToTask(taskDto)));
    byDate_->addTask(sft);
    byPriority_->addTask(sft);

    storage_.addTask(std::move(sft));
    return TaskCreationResult::success(id);
}

TaskCreationResult TaskService::addSubtask(TaskID taskID, const TaskDTO &subTask){
    auto subtaskID = addTask(subTask);
    std::optional<std::weak_ptr<FullTask>> ft = storage_.getTask(taskID);
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

std::vector<TaskDTO> TaskService::getAllTasksByPriority(){
    auto v = byPriority_->getAllTasksByPrior();
    std::vector<TaskDTO> vec;
    for(auto i: v)
        vec.push_back(TaskConvertor::transferToTaskDTO(i));

    return vec;
}

std::vector<TaskDTO> TaskService::getTasksForToday(){
    time_t now = time(0);
    auto cur = std::make_unique<tm>(*gmtime(&now));
    Date date = Date::create(cur->tm_year+1900, cur->tm_mon + 1, cur->tm_mday);

    auto v = byDate_->getTasksForToday(date);
    std::vector<TaskDTO> vec;
    for(auto i: v)
        vec.push_back(TaskConvertor::transferToTaskDTO(i));

    return vec;
}

std::vector<TaskDTO> TaskService::getTasksForWeek(){
    time_t now = time(0);
    auto cur = std::make_unique<tm>(*gmtime(&now));
    Date date = Date::create(cur->tm_year+1900, cur->tm_mon + 1, cur->tm_mday);

    auto v = byDate_->getTasksForWeek(date);
    std::vector<TaskDTO> vec;
    for(auto i: v)
        vec.push_back(TaskConvertor::transferToTaskDTO(i));

    return vec;
};

void TaskService::removeTask(TaskID id){
    auto fullTask = storage_.getTask(id);
    if(fullTask.has_value()) {
        byDate_->deleteTask(fullTask.value());
        byPriority_->deleteTask(fullTask.value());
    }
}

std::optional<TaskDTO> TaskService::getTask(TaskID id){
    std::optional<std::weak_ptr<FullTask>> ft = storage_.getTask(id);
    if (ft.has_value())
        return
            std::optional<TaskDTO>(TaskConvertor::transferToTaskDTO(ft.value()));
     else
         return std::nullopt;
}


