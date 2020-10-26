//
// Created by ilya on 25.10.2020.
//

#ifndef TODOLIST_GRPCSERVER_H
#define TODOLIST_GRPCSERVER_H

#include <iostream>
#include <memory>
#include <string>

#include <grpcpp/grpcpp.h>
#include <grpcpp/health_check_service_interface.h>
#include <grpcpp/ext/proto_server_reflection_plugin.h>
#include "TaskService.grpc.pb.h"
#include "TaskService.pb.h"
#include "Core/model/DataInterface.h"


using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;


class GRPCServer final : public GrpcTaskService::Service {
public:
    explicit GRPCServer(std::unique_ptr<DataInterface> model)
    :
    model_(std::move(model))
    {}
public:
    Status addTask(ServerContext* context, const TaskStructure* request, AddTaskResponse* response) override;
    Status addSubtask(ServerContext* context, const AddSubTaskRequest* request, AddTaskResponse* response) override;
    Status deleteTask(ServerContext* context, const TaskIDRequest* request, RequstTaskResponse* response)override;
    Status complete(ServerContext* context, const TaskIDRequest* request, RequstTaskResponse* response)override;
    Status postponeTask(ServerContext* context,const PostponeRequest* request, RequstTaskResponse* response)override;
    Status editTask(ServerContext* context,const EditRequest* request, RequstTaskResponse* response)override;
public:
    Status save(ServerContext* context, const PersistentRequest* request,RequstTaskResponse* response)override;
    Status load(ServerContext* context, const PersistentRequest* request,RequstTaskResponse* response)override;
public:
    Status getTaskByID (ServerContext* context, const TaskIDRequest* request,GetTaskByIDResponse* response) override;
    Status getSubtasks(ServerContext* context, const TaskIDRequest* request,GetTasksResponse* response)override;
    Status getAllTasksByPriority(ServerContext* context, const EmptyRequest* request,GetTasksResponse* response)override;
    Status getTasksForToday(ServerContext* context, const EmptyRequest* request,GetTasksResponse* response)override;
    Status getTasksForWeek(ServerContext* context, const EmptyRequest* request,GetTasksResponse* response)override;
private:
    std::unique_ptr<DataInterface> model_;
};



#endif //TODOLIST_GRPCSERVER_H
