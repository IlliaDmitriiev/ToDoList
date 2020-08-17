//
// Created by illia.dmitriiev on 7/27/2020.
//

#include "TaskService.h"
#include "ReturnTypeCreator.h"

AddTaskResult TaskService::addTask(const TaskDTO &taskDTO){

    TaskID id = generator_->generateId();
    auto shared_task = std::make_shared<FullTask>(FullTask::create(id, TaskConvertor::transferToTask(taskDTO)));

    if (byDate_->addTask(shared_task) &&
    byPriority_->addTask(shared_task) &&
    storage_->addTask(std::move(shared_task))) {
        return operation_result::TaskAddedSuccessful(id);
    }
    else {
        return operation_result::TaskAddedUnsuccessful("can't put task in storage");
    }
}

AddTaskResult TaskService::addSubtask(TaskID taskID, const TaskDTO &subTask){
    std::optional<std::weak_ptr<FullTask>> weak_task = storage_->getTask(taskID);

    if(weak_task.has_value()) {
        auto subtask_result = addTask(subTask);

        if (subtask_result.id.has_value()) {
            auto subtask = storage_->getTask(subtask_result.id.value());
            weak_task.value().lock()->addSubtask(subtask.value());

            return operation_result::TaskAddedSuccessful(subtask_result.id.value());
        }
        else {
            return operation_result::TaskAddedUnsuccessful("subtask creation is failed");
        }
    }
    else {
        return operation_result::TaskAddedUnsuccessful("task not found");
    }
}

RequstTaskResult TaskService::complete(TaskID id){
    auto node = storage_->getTask(id);
    if(node.has_value()){
        node.value().lock()->complete();
        return operation_result::TaskRequestedSuccessful();
    }
    else {
        return operation_result::TaskRequestedUnsuccessful("task not found");
    }

}

RequstTaskResult TaskService::postponeTask(TaskID id, boost::gregorian::date new_date){
    auto task = storage_->getTask(id);
    if(task.has_value()){
        task.value().lock()->postpone(new_date);
        return operation_result::TaskRequestedSuccessful();
    }
    else {
        return operation_result::TaskRequestedUnsuccessful("task not found");
    }

}

std::vector<TaskDTO> TaskService::getAllTasksByPriority(){
    auto v = byPriority_->getAllTasksByPrior();
    std::vector<TaskDTO> vec;
    for(auto &i: v) {
        vec.push_back(TaskConvertor::transferToTaskDTO(i));
    }

    return vec;
}

std::vector<TaskDTO> TaskService::getTasksForToday(){
    boost::gregorian::date date{boost::gregorian::day_clock::local_day()};

    auto v = byDate_->getTasksForToday(date);
    std::vector<TaskDTO> vec;
    for(auto &i: v) {
        vec.push_back(TaskConvertor::transferToTaskDTO(i));
    }

    return vec;
}

std::vector<TaskDTO> TaskService::getTasksForWeek(){
    boost::gregorian::date date{boost::gregorian::day_clock::local_day()};

    auto v = byDate_->getTasksForWeek(date);
    std::vector<TaskDTO> vec;
    for(auto &i: v) {
        vec.push_back(TaskConvertor::transferToTaskDTO(i));
    }
    return vec;
};

RequstTaskResult TaskService::deleteTask(TaskID id){
    auto task = storage_->getTask(id);

    if(task.has_value()) {

        for(TaskID subtaskID: task.value().lock()->getSubtasks())
             deleteTask(subtaskID);

        if(!removeTask(task.value().lock())) {
            return operation_result::TaskRequestedUnsuccessful("deleting is failed");
        }
        if(storage_->deleteTask(task.value().lock()->getId())) {
            return operation_result::TaskRequestedSuccessful();
        }
        else {
            return operation_result::TaskRequestedUnsuccessful("can't get task from storage");
        }
    }
    else {
        return operation_result::TaskRequestedUnsuccessful("task not found");
    }
}

bool TaskService::removeTask(const std::weak_ptr<FullTask> &task){
    return
        byDate_->deleteTask(task) &&
        byPriority_->deleteTask(task) &&
        storage_->deleteSubtaskInParent(task.lock()->getParent(), task.lock()->getId());
}

std::optional<TaskDTO> TaskService::getTask(TaskID id){
    std::optional<std::weak_ptr<FullTask>> ft = storage_->getTask(id);
    if (ft.has_value()) {
        return std::optional<TaskDTO>(TaskConvertor::transferToTaskDTO(ft.value()));
    }
    else {
        return std::nullopt;
    }
}


