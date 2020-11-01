//
// Created by ilya on 31.10.2020.
//

#include "ClientServer.h"
#include "CLI/Utils/Convertors/ProtoConvertor.h"

AddTaskResult ClientServer::addTask(const TaskDTO &taskDto) {
    grpc::ClientContext context;
    AddTaskResponse response;
    auto status = stub_->addTask(&context,
                                 ProtoConvertor::transferToProtoTask(taskDto),
                                 &response);
    return ProtoConvertor::transferToReturnType(response);
}

AddTaskResult ClientServer::addSubtask(TaskID taskID, const TaskDTO &subtask) {
    grpc::ClientContext context;
    AddTaskResponse response;
    AddSubTaskRequest param;
    auto proto_task = std::make_unique<TaskStructure>(ProtoConvertor::transferToProtoTask(subtask));
    param.set_allocated_task(proto_task.release());
    param.set_allocated_parent(new TaskIDRequest);
    param.mutable_parent()->set_id(taskID.ID());
    auto status = stub_->addSubtask(&context,
                                    param,
                                    &response);
    return ProtoConvertor::transferToReturnType(response);
}

RequstTaskResult ClientServer::deleteTask(TaskID id) {
    grpc::ClientContext context;
    RequstTaskResponse response;
    TaskIDRequest param;
    param.set_id(id.ID());
    auto status = stub_->deleteTask(&context,
                                    param,
                                    &response);
    return ProtoConvertor::transferToReturnType(response);
}

RequstTaskResult ClientServer::complete(TaskID id) {
    grpc::ClientContext context;
    RequstTaskResponse response;
    TaskIDRequest param;
    param.set_id(id.ID());
    auto status = stub_->complete(&context,
                                  param,
                                  &response);
    return ProtoConvertor::transferToReturnType(response);
}

RequstTaskResult ClientServer::postponeTask(TaskID id, boost::gregorian::date new_date) {
    grpc::ClientContext context;
    RequstTaskResponse response;
    auto id_request = std::make_unique<TaskIDRequest>();
    id_request->set_id(id.ID());
    PostponeRequest param;
    param.set_allocated_id(id_request.release());
    param.set_date(new_date.day_number());
    auto status = stub_->postponeTask(&context,
                                      param,
                                      &response);
    return ProtoConvertor::transferToReturnType(response);
}

RequstTaskResult ClientServer::editTask(TaskID id, const TaskDTO &dto) {
    grpc::ClientContext context;
    RequstTaskResponse response;
    auto id_request = std::make_unique<TaskIDRequest>();
    id_request->set_id(id.ID());
    auto proto_task = std::make_unique<TaskStructure>(ProtoConvertor::transferToProtoTask(dto));
    EditRequest param;
    param.set_allocated_id(id_request.release());
    param.set_allocated_task(proto_task.release());
    auto status = stub_->editTask(&context,
                                  param,
                                  &response);
    return ProtoConvertor::transferToReturnType(response);
}

std::vector<TaskDTO> ClientServer::getSubtasks(TaskID id) {
    grpc::ClientContext context;
    GetTasksResponse response;
    TaskIDRequest param;
    param.set_id(id.ID());
    auto status = stub_->getSubtasks(&context,
                                     param,
                                     &response);
    std::vector<TaskDTO> result;
    for (auto &task: response.tasks()){
        result.push_back(ProtoConvertor::transferToTaskDTO(task));
    }
    return result;
}

std::vector<TaskDTO> ClientServer::getAllTasksByPriority() {
    grpc::ClientContext context;
    GetTasksResponse response;
    EmptyRequest param;

    auto status = stub_->getAllTasksByPriority(&context,
                                               param,
                                               &response);
    std::vector<TaskDTO> result;
    for (auto &task: response.tasks()){
        result.push_back(ProtoConvertor::transferToTaskDTO(task));
    }
    return result;
}

std::vector<TaskDTO> ClientServer::getTasksForToday() {
    grpc::ClientContext context;
    GetTasksResponse response;
    EmptyRequest param;

    auto status = stub_->getTasksForToday(&context,
                                          param,
                                          &response);
    std::vector<TaskDTO> result;
    for (auto &task: response.tasks()){
        result.push_back(ProtoConvertor::transferToTaskDTO(task));
    }
    return result;
}

std::vector<TaskDTO> ClientServer::getTasksForWeek() {
    grpc::ClientContext context;
    GetTasksResponse response;
    EmptyRequest param;

    auto status = stub_->getTasksForWeek(&context,
                                         param,
                                         &response);
    std::vector<TaskDTO> result;
    for (auto &task: response.tasks()){
        result.push_back(ProtoConvertor::transferToTaskDTO(task));
    }
    return result;
}

std::optional<TaskDTO> ClientServer::getTask(TaskID id) {
    grpc::ClientContext context;
    GetTaskByIDResponse response;
    TaskIDRequest param;
    param.set_id(id.ID());
    auto status = stub_->getTaskByID(&context,
                                     param,
                                     &response);
    if (status.ok()) {
        return ProtoConvertor::transferToTaskDTO(response.task());
    }
    else {
        return std::nullopt;
    }
}

RequstTaskResult ClientServer::save(const std::string& filename){
    grpc::ClientContext context;
    RequstTaskResponse response;
    PersistentRequest param;
    param.set_filename(filename);
    auto status = stub_->save(&context,
                              param,
                              &response);
    return ProtoConvertor::transferToReturnType(response);
}

RequstTaskResult ClientServer::load(const std::string& filename) {
    grpc::ClientContext context;
    RequstTaskResponse response;
    PersistentRequest param;
    param.set_filename(filename);
    auto status = stub_->load(&context,
                              param,
                              &response);
    return ProtoConvertor::transferToReturnType(response);
}
 
