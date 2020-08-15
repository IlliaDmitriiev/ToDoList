//
// Created by illia.dmitriiev on 7/27/2020.
//

#include "TaskService.h"
#include "ReturnTypeCreator.h"

AddTaskResult TaskService::addTask(const TaskDTO &taskDTO){

    TaskID id = generator_.generateId();
    auto shared_task = std::make_shared<FullTask>(FullTask::create(id, TaskConvertor::transferToTask(taskDTO)));

    if (byDate_->addTask(shared_task) &&
    byPriority_->addTask(shared_task) &&
    storage_->addTask(std::move(shared_task)))
        return operation_result::TaskAddedSuccessful(id);
    else
        return operation_result::TaskAddedUnsuccessful("can't put task in storage");
}

AddTaskResult TaskService::addSubtask(TaskID taskID, const TaskDTO &subTask){
    auto subtask_result = addTask(subTask);
    std::optional<std::weak_ptr<FullTask>> ft = storage_->getTask(taskID);

    if(ft.has_value()) {
        if (subtask_result.id.has_value()) {
            ft.value().lock()->addSubtask(storage_->getTask(subtask_result.id.value()).value());
            return operation_result::TaskAddedSuccessful(subtask_result.id.value());
        }
        else
            return operation_result::TaskAddedUnsuccessful("subtask creation is failed");
    }
    else
        return operation_result::TaskAddedUnsuccessful("task not found");

}

RequstTaskResult TaskService::complete(TaskID id){
    auto node = storage_->getTask(id);
    if(node.has_value()){
        node.value().lock()->complete();
        return operation_result::TaskRequestedSuccessful();
    }
    else
        return operation_result::TaskRequestedUnsuccessful("task not found");

}

RequstTaskResult TaskService::postponeTask(TaskID id, boost::gregorian::date new_date){
    auto task = storage_->getTask(id);
    if(task.has_value()){
        task.value().lock()->postpone(new_date);
        return operation_result::TaskRequestedSuccessful();
    }
    else
        return operation_result::TaskRequestedUnsuccessful("task not found");

}

std::vector<TaskDTO> TaskService::getAllTasksByPriority(){
    auto v = byPriority_->getAllTasksByPrior();
    std::vector<TaskDTO> vec;
    for(auto &i: v)
        vec.push_back(TaskConvertor::transferToTaskDTO(i));

    return vec;
}

std::vector<TaskDTO> TaskService::getTasksForToday(){
    time_t now = time(0);
    auto cur = std::make_unique<tm>(*gmtime(&now));
    boost::gregorian::date date(cur->tm_year+1900, cur->tm_mon + 1, cur->tm_mday);

    auto v = byDate_->getTasksForToday(date);
    std::vector<TaskDTO> vec;
    for(auto &i: v)
        vec.push_back(TaskConvertor::transferToTaskDTO(i));

    return vec;
}

std::vector<TaskDTO> TaskService::getTasksForWeek(){
    time_t now = time(0);
    auto cur = std::make_unique<tm>(*gmtime(&now));
    boost::gregorian::date date(cur->tm_year+1900, cur->tm_mon + 1, cur->tm_mday);

    auto v = byDate_->getTasksForWeek(date);
    std::vector<TaskDTO> vec;
    for(auto &i: v)
        vec.push_back(TaskConvertor::transferToTaskDTO(i));

    return vec;
};

RequstTaskResult TaskService::deleteTask(TaskID id){
    auto task = storage_->getTask(id);

    if(task.has_value()) {
        RequstTaskResult subtask_results;
        subtask_results.result = ResultType::SUCCESS;

        for(TaskID subtaskID: task.value().lock()->getSubtasks()) {
            RequstTaskResult subtask_result = deleteTask(subtaskID);
            if (subtask_result.result == ResultType::FAILURE)
                subtask_results = subtask_result;
        }

        if(!removeTask(task.value().lock()))
            return operation_result::TaskRequestedUnsuccessful("delete of subtasks is failed");

        storage_->deleteTask(task.value().lock()->getId());
        return subtask_results;
    }
    else
        return operation_result::TaskRequestedUnsuccessful("task not found");
}

bool TaskService::removeTask(const std::weak_ptr<FullTask> &task){
    return
        byDate_->deleteTask(task) &&
        byPriority_->deleteTask(task) &&
        storage_->deleteSubtaskInParent(task.lock()->getParent(), task.lock()->getId());
}

std::optional<TaskDTO> TaskService::getTask(TaskID id){
    std::optional<std::weak_ptr<FullTask>> ft = storage_->getTask(id);
    if (ft.has_value())
        return std::optional<TaskDTO>(TaskConvertor::transferToTaskDTO(ft.value()));
    else
        return std::nullopt;
}


