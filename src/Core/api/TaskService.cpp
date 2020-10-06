//
// Created by illia.dmitriiev on 7/27/2020.
//

#include "TaskService.h"
#include "Core/utils/ReturnTypeCreator.h"
#include "Core/utils/DataHolderCreator.h"
#include "Core/persistence/ModelPersister.h"

AddTaskResult TaskService::addTask(const ServiceTaskDTO &taskDTO){
    return model_->addTask(TaskConvertor::transferToModelDTO(taskDTO));
}

AddTaskResult TaskService::addSubtask(TaskID taskID, const ServiceTaskDTO &subTask){
    return model_->addSubtask(taskID,TaskConvertor::transferToModelDTO(subTask));
}

RequstTaskResult TaskService::complete(TaskID id){
    return model_->complete(id);
}

RequstTaskResult TaskService::postponeTask(TaskID id, boost::gregorian::date new_date){
    auto task = getTask(id);
    if (task.has_value()){
        return model_->editTask(id, ModelTaskDTO::create(id,
                                                         new_date,
                                                         task.value().getName(),
                                                         task.value().getLabel(),
                                                         task.value().getPriority(),
                                                         task.value().isCompleted()));
    }
    else {
        return operation_result::TaskRequestedUnsuccessful("task not found");
    }

}

RequstTaskResult TaskService::editTask(TaskID id, const ServiceTaskDTO &task) {
   return model_->editTask(id, TaskConvertor::transferToModelDTO(task));
}

std::vector<ServiceTaskDTO> TaskService::getSubtasks(TaskID id) {
    auto model_subtasks = model_->getSubtasks(id);
    std::vector<ServiceTaskDTO> subtasks;
    for(const auto& subtask: model_subtasks){
        subtasks.push_back(TaskConvertor::transferToServiceDTO(subtask));
    }

    return subtasks;
}

std::vector<ServiceTaskDTO> TaskService::getAllTasksByPriority(){
    auto model_tasks = model_->getAllTasksByPriority();
    std::vector<ServiceTaskDTO> subtasks;
    for(const auto& subtask: model_tasks){
        subtasks.push_back(TaskConvertor::transferToServiceDTO(subtask));
    }

    return subtasks;
}

std::vector<ServiceTaskDTO> TaskService::getTasksForToday(){
    auto model_tasks = model_->getTasksForToday();
    std::vector<ServiceTaskDTO> subtasks;
    for(const auto& subtask : model_tasks){
        subtasks.push_back(TaskConvertor::transferToServiceDTO(subtask));
    }

    return subtasks;
}

std::vector<ServiceTaskDTO> TaskService::getTasksForWeek(){
    auto model_tasks = model_->getTasksForWeek();
    std::vector<ServiceTaskDTO> subtasks;
    for(const auto& subtask: model_tasks){
        subtasks.push_back(TaskConvertor::transferToServiceDTO(subtask));
    }

    return subtasks;
};

RequstTaskResult TaskService::deleteTask(TaskID id){
    return model_->deleteTask(id);
}


std::optional<ServiceTaskDTO> TaskService::getTask(TaskID id){
    auto task = model_->getTask(id);
    if (task.has_value()){
        return TaskConvertor::transferToServiceDTO(task.value());
    }
    else {
        return std::nullopt;
    }
}

RequstTaskResult TaskService::save(){
    std::fstream file("file1.txt", std::fstream::out);
    auto persister = std::make_unique<ModelPersister>(*model_, file);
    if (persister->save()){
        return operation_result::TaskRequestedSuccessful();
    }
    else {
        return operation_result::TaskRequestedUnsuccessful("errors occurred while saving");
    }
}

RequstTaskResult TaskService::load(){
    std::fstream file("file1.txt", std::fstream::in);
    auto new_model = todo_list_model::createDataHolder();
    auto persister = std::make_unique<ModelPersister>(*new_model, file);
    if (persister->load()){
        model_.reset();
        model_= std::move(new_model);
        return operation_result::TaskRequestedSuccessful();
    }
    else {
        return operation_result::TaskRequestedUnsuccessful("errors occurred while saving");
    }
}
