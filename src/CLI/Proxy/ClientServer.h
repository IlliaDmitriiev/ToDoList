//
// Created by ilya on 31.10.2020.
//

#ifndef TODOLIST_CLIENTSERVER_H
#define TODOLIST_CLIENTSERVER_H

#include "TaskService.grpc.pb.h"
#include "Proxy.h"
#include <grpcpp/grpcpp.h>

/*
 * Proxy server.
 * It make remotes requests to real server.
 */
class ClientServer: public Proxy {
public:
    explicit ClientServer(const std::shared_ptr<grpc::Channel>& channel)
            : stub_(GrpcTaskService::NewStub(channel)) {}
public:

    AddTaskResult addTask(const TaskDTO &taskDto) override;

    AddTaskResult addSubtask(TaskID taskID, const TaskDTO &subtask) override;

    RequstTaskResult deleteTask(TaskID id) override;

    RequstTaskResult complete(TaskID id) override;

    RequstTaskResult postponeTask(TaskID id, boost::gregorian::date new_date) override;

    RequstTaskResult editTask(TaskID id, const TaskDTO &subtask) override;

public:
    std::vector<TaskDTO> getSubtasks(TaskID id) override;

    std::vector<TaskDTO> getAllTasksByPriority() override;

    std::vector<TaskDTO> getTasksForToday() override;

    std::vector<TaskDTO> getTasksForWeek() override;

    std::optional<TaskDTO> getTask(TaskID id) override;

public:
    RequstTaskResult save(const std::string&) override;

    RequstTaskResult load(const std::string&) override;

private:
    std::unique_ptr<GrpcTaskService::Stub> stub_;
};


#endif //TODOLIST_CLIENTSERVER_H
