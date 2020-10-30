//
// Created by ilya on 26.10.2020.
//

#ifndef TODOLIST_PROTORESPONSE_H
#define TODOLIST_PROTORESPONSE_H

#include "TaskService.grpc.pb.h"
#include "Core/api/ReturnType.h"
#include <memory>

class ProtoResponse{
public:
    static void fill(AddTaskResult result, AddTaskResponse *response) {
        if (ResultType::SUCCESS == result.result) {
            auto id = std::make_unique<TaskIDRequest>();
            id->set_id(result.id->getId());
            response->set_allocated_created_id(id.release());
            response->set_success(true);
        } else {
            response->set_success(false);
            response->set_error_message(result.error_message);
        }
    }

    static void fill(RequstTaskResult result, RequstTaskResponse* response){
        if (ResultType::SUCCESS == result.result) {
            response->set_success(true);
        }
        else {
            response->set_success(false);
            response->set_error_message(result.error_message);
        }
    }
};

#endif //TODOLIST_PROTORESPONSE_H
