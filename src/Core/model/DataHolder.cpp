//
// Created by ilya on 24.09.2020.
//

#include "DataHolder.h"

AddTaskResult DataHolder::addTask(const ModelTaskDTO &taskDTO){

    TaskID id = generator_->generateId();
    auto shared_task = std::make_shared<FullTask>(FullTask::create(id, ModelTaskConvertor::transferToTask(taskDTO)));

    if (byDate_->addTask(shared_task) &&
        byPriority_->addTask(shared_task) &&
        storage_->addTask(std::move(shared_task))) {
        return operation_result::TaskAddedSuccessful(id);
    }
    else {
        return operation_result::TaskAddedUnsuccessful("can't put task in storage");
    }
}

AddTaskResult DataHolder::addSubtask(TaskID taskID, const ModelTaskDTO &subTask){
    auto task = storage_->getTask(taskID);

    if(task.has_value()) {
        auto subtask_result = addTask(subTask);

        if (subtask_result.id.has_value()) {
            auto subtask = storage_->getTask(subtask_result.id.value());
            task.value().lock()->addSubtask(subtask.value());

            return operation_result::TaskAddedSuccessful(subtask_result.id.value());
        }
        else {
            return operation_result::TaskAddedUnsuccessful("subtask creation is failed");
        }
    }
    else {
        return operation_result::TaskAddedUnsuccessful("root task with the given id was not found");
    }
}

RequstTaskResult DataHolder::complete(TaskID id){
    auto task = storage_->getTask(id);
    if(task.has_value()){
        task.value().lock()->complete();
        return operation_result::TaskRequestedSuccessful();
    }
    else {
        return operation_result::TaskRequestedUnsuccessful("task not found");
    }

}

RequstTaskResult DataHolder::editTask(TaskID id, const ModelTaskDTO &subtask) {
    auto task = storage_->getTask(id);
    if(task.has_value()){
        task.value().lock()->change(ModelTaskConvertor::transferToTask(subtask));
        return operation_result::TaskRequestedSuccessful();
    }
    else {
        return operation_result::TaskRequestedUnsuccessful("task not found");
    }

}

std::vector<ModelTaskDTO> DataHolder::getSubtasks(TaskID id) {
    std::vector<ModelTaskDTO> vec;
    auto node = storage_->getTask(id);
    if(node.has_value()){
        auto subtasks_id = node.value().lock()->getSubtasks();
        for(auto &i: subtasks_id) {
            auto subtask = storage_->getTask(i);
            if (subtask.has_value()) {
                vec.push_back(ModelTaskConvertor::transferToModelTaskDTO(*subtask.value().lock()));
            }
        }
    }

    return vec;
}
RequstTaskResult DataHolder::deleteTask(TaskID id){
    auto task = storage_->getTask(id);

    if(task.has_value()) {

        for(TaskID subtaskID: task.value().lock()->getSubtasks()){
            deleteTask(subtaskID);
        }

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

bool DataHolder::removeTask(const std::weak_ptr<FullTask> &task){
    return
            byDate_->deleteTask(task) &&
            byPriority_->deleteTask(task) &&
            storage_->deleteSubtaskInParent(task.lock()->getParent(), task.lock()->getId());
}

std::vector<ModelTaskDTO> DataHolder::getAllTasks() {
    auto tasks = storage_->getAllTasks();
    std::vector<ModelTaskDTO> DTOTasks;
    for(auto &i: tasks) {
        DTOTasks.push_back(ModelTaskConvertor::transferToModelTaskDTO(*i.lock()));
    }
    return DTOTasks;
}

std::optional<ModelTaskDTO> DataHolder::getTask(TaskID id){
    auto task = storage_->getTask(id);
    if (task.has_value()) {
        return std::optional<ModelTaskDTO>(ModelTaskConvertor::transferToModelTaskDTO(*task.value().lock()));
    }
    else {
        return std::nullopt;
    }
}


std::vector<ModelTaskDTO> DataHolder::getAllTasksByPriority(){
    auto v = byPriority_->getAllTasksByPrior();
    std::vector<ModelTaskDTO> vec;
    for(auto &i: v) {
        vec.push_back(ModelTaskConvertor::transferToModelTaskDTO(*i.lock()));
    }

    return vec;
}

std::vector<ModelTaskDTO> DataHolder::getTasksForToday(){
    boost::gregorian::date date{boost::gregorian::day_clock::local_day()};

    auto v = byDate_->getTasksForToday(date);
    std::vector<ModelTaskDTO> vec;
    for(auto &i: v) {
        vec.push_back(ModelTaskConvertor::transferToModelTaskDTO(*i.lock()));
    }

    return vec;
}

std::vector<ModelTaskDTO> DataHolder::getTasksForWeek(){
    boost::gregorian::date date{boost::gregorian::day_clock::local_day()};

    auto v = byDate_->getTasksForWeek(date);
    std::vector<ModelTaskDTO> vec;
    for(auto &i: v) {
        vec.push_back(ModelTaskConvertor::transferToModelTaskDTO(*i.lock()));
    }
    return vec;
}
