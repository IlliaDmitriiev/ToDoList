//
// Created by illia.dmitriiev on 7/27/2020.
//

#include "TaskService.h"

AddTaskResult TaskService::addTask(const TaskDTO &taskDTO){
    AddTaskResult task_result;
    TaskID id = generator_.generateId();
    auto shared_task = std::make_shared<FullTask>(FullTask::create(id, TaskConvertor::transferToTask(taskDTO)));

    byDate_->addTask(shared_task);
    byPriority_->addTask(shared_task);
    storage_.addTask(std::move(shared_task));

    task_result.result = ResultType::SUCCESS;
    task_result.id = id;
    return task_result;
}

AddTaskResult TaskService::addSubtask(TaskID taskID, const TaskDTO &subTask){
    AddTaskResult task_result;
    auto subtask_result = addTask(subTask);
    std::optional<std::weak_ptr<FullTask>> ft = storage_.getTask(taskID);

    if(ft.has_value()) {
        if (subtask_result.id.has_value()) {
            ft.value().lock()->addSubtask(storage_.getTask(subtask_result.id.value()).value());
            task_result.result = ResultType::SUCCESS;
            task_result.id = subtask_result.id.value();
            return task_result;
        }
        else {
            task_result.result = ResultType::FAILURE;
            task_result.id = std::nullopt;
            task_result.error_message = "subtask creation is failed";
            return task_result;
        }
    }
    else {
        task_result.result = ResultType::FAILURE;
        task_result.id = std::nullopt;
        task_result.error_message = "task not found";
        return task_result;
    }
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

RequstTaskResult TaskService::deleteTask(TaskID id){
    RequstTaskResult task_result;
    auto task = storage_.getTask(id);
    if(task.has_value()) {

        RequstTaskResult subtask_results;
        subtask_results.result = ResultType::SUCCESS;

        for(TaskID subtaskID: task.value().lock()->getSubtasks()) {
            RequstTaskResult subtask_result = deleteTask(subtaskID);
            if (subtask_result.result == ResultType::FAILURE)
                subtask_results = subtask_result;
        }

        if(!removeTask(task.value().lock())) {
            task_result.result = ResultType::FAILURE;
            task_result.error_message = "delete of subtasks is failed";
            return task_result;
        }
        storage_.deleteTask(task.value().lock()->getId());
        return subtask_results;
    }
    else {
        task_result.result = ResultType::FAILURE;
        task_result.error_message = "task not found";
        return task_result;
    }
}

bool TaskService::removeTask(const std::weak_ptr<FullTask> &task){
    return
        byDate_->deleteTask(task) &&
        byPriority_->deleteTask(task) &&
        storage_.deleteSubtaskInParent(task.lock()->getParent(), task.lock()->getId());
}

std::optional<TaskDTO> TaskService::getTask(TaskID id){
    std::optional<std::weak_ptr<FullTask>> ft = storage_.getTask(id);
    if (ft.has_value())
        return
            std::optional<TaskDTO>(TaskConvertor::transferToTaskDTO(ft.value()));
     else return std::nullopt;
}


