//
// Created by ilya on 25.10.2020.
//

#include "GRPCServer.h"
#include "Core/utils/ProtoTaskConvertor.h"
#include <future>
#include "fstream"
#include "Core/utils/DataHolderCreator.h"
#include "Core/utils/ProtoResponse.h"
#include "Core/persistence/ModelPersister.h"


Status GRPCServer::addTask(ServerContext* context,
                           const TaskStructure* request,
                           AddTaskResponse* response)
{
    auto model_response =  model_->addTask(ProtoTaskConvertor::transferToModelTask(*request));
    ProtoResponse::fill(model_response, response);
    return Status::OK;
}

Status GRPCServer::addSubtask(ServerContext* context,
                              const AddSubTaskRequest* request,
                              AddTaskResponse* response)
{
    auto model_response =  model_->addSubtask(TaskID::create(request->parent().id()),
                                              ProtoTaskConvertor::transferToModelTask(request->task()));
    ProtoResponse::fill(model_response, response);
    return Status::OK;
}

Status GRPCServer::deleteTask(ServerContext* context,
                              const TaskIDRequest* request,
                              RequstTaskResponse* response)
{
    auto model_response =  model_->deleteTask(TaskID::create(request->id()));
    ProtoResponse::fill(model_response, response);
    return Status::OK;
}

Status GRPCServer::complete(ServerContext* context,
                            const TaskIDRequest* request,
                            RequstTaskResponse* response)
{
    auto model_response =  model_->complete(TaskID::create(request->id()));
    ProtoResponse::fill(model_response, response);
    return Status::OK;
}
Status GRPCServer::postponeTask(ServerContext* context,
                                const PostponeRequest* request,
                                RequstTaskResponse* response)
{

    auto task = model_->getTask(TaskID::create(request->id().id()));
    if (task.has_value()){
        auto model_response = model_->editTask(task.value().getId(),
                                               ModelTaskDTO::create (task.value().getId(),
                                               boost::gregorian::date{request->date()},
                                               task.value().getName(),
                                               task.value().getLabel(),
                                               task.value().getPriority(),
                                               task.value().isCompleted()));
        ProtoResponse::fill(model_response, response);
    }
    else {
        ProtoResponse::fill(operation_result::TaskRequestedUnsuccessful("task not found"), response);
    }
    return Status::OK;
}

Status GRPCServer::editTask(ServerContext* context,
                            const EditRequest* request,
                            RequstTaskResponse* response)
{
    auto model_response =  model_->editTask(TaskID::create(request->id().id()),
                                            ProtoTaskConvertor::transferToModelTask(request->task()));
    ProtoResponse::fill(model_response, response);
    return Status::OK;
}

Status GRPCServer::save(ServerContext* context,
                        const PersistentRequest* request,
                        RequstTaskResponse* response)
{
    std::fstream file(request->filename(), std::fstream::out);
    auto persister = std::make_unique<ModelPersister>(*model_, file);

    auto save_result = std::async(std::bind(&Persister::save, persister.get()));
    save_result.wait();
    file.close();

    if (save_result.get()){
        ProtoResponse::fill(operation_result::TaskRequestedSuccessful(),response);
    }
    else {
        ProtoResponse::fill(operation_result::TaskRequestedUnsuccessful("errors occurred while saving"),response);
    }
    return Status::OK;
}

Status GRPCServer::load(ServerContext* context,
                        const PersistentRequest* request,
                        RequstTaskResponse* response)
{
    std::fstream file(request->filename(), std::fstream::in);
    auto new_model = todo_list_model::createDataHolder();
    auto persister = std::make_unique<ModelPersister>(*new_model, file);

    auto load_result = std::async(std::bind(&Persister::load, persister.get()));
    load_result.wait();
    file.close();

    if (load_result.get()){
        model_.reset();
        model_= std::move(new_model);
        ProtoResponse::fill( operation_result::TaskRequestedSuccessful(),response);
    }
    else {
        ProtoResponse::fill(operation_result::TaskRequestedUnsuccessful("errors occurred while saving"),response);
    }
    return Status::OK;
}

Status GRPCServer::getTaskByID (ServerContext* context,
                                const TaskIDRequest* request,
                                GetTaskByIDResponse* response)
{
    auto model_task = model_->getTask(TaskID::create(request->id()));
    if (model_task.has_value()){
        auto task = ProtoTaskConvertor::transferToTaskStructure(model_task.value());
        auto proto_task = std::make_unique<TaskStructure>(task);
        response->set_allocated_task(proto_task.release());

        return Status::OK;
    }
    response->set_allocated_task(nullptr);
    return Status::CANCELLED;
}

Status GRPCServer::getSubtasks(ServerContext* context,
                               const TaskIDRequest* request,
                               GetTasksResponse* response)
{
    auto model_subtasks = model_->getSubtasks(TaskID::create(request->id()));
    for(const auto& subtask: model_subtasks){
        auto *proto_task = response->add_tasks();
        auto task = ProtoTaskConvertor::transferToTaskStructure(subtask);

        proto_task->set_name(task.name());
        proto_task->set_label(task.label());
        proto_task->set_prior(task.prior());
        proto_task->set_date(task.date());
        proto_task->set_completed(task.completed());
    }

    return Status::OK;

}

Status GRPCServer::getAllTasksByPriority(ServerContext* context,
                                         const EmptyRequest* request,
                                         GetTasksResponse* response)
{
    auto model_tasks = model_->getAllTasksByPriority();
    for(const auto& model_task: model_tasks){
        auto *proto_task = response->add_tasks();
        auto task = ProtoTaskConvertor::transferToTaskStructure(model_task);

        proto_task->set_name(task.name());
        proto_task->set_label(task.label());
        proto_task->set_prior(task.prior());
        proto_task->set_date(task.date());
        proto_task->set_completed(task.completed());
    }

    return Status::OK;
}

Status GRPCServer::getTasksForToday(ServerContext* context,
                                    const EmptyRequest* request,
                                    GetTasksResponse* response)
{
    auto model_tasks = model_->getTasksForToday();
    for(const auto& model_task: model_tasks){
        auto *proto_task = response->add_tasks();
        auto task = ProtoTaskConvertor::transferToTaskStructure(model_task);

        proto_task->set_name(task.name());
        proto_task->set_label(task.label());
        proto_task->set_prior(task.prior());
        proto_task->set_date(task.date());
        proto_task->set_completed(task.completed());
    }

    return Status::OK;
}

Status GRPCServer::getTasksForWeek(ServerContext* context,
                                   const EmptyRequest* request,
                                   GetTasksResponse* response)
{
    auto model_tasks = model_->getTasksForWeek();
    for(const auto& model_task: model_tasks){
        auto *proto_task = response->add_tasks();
        auto task = ProtoTaskConvertor::transferToTaskStructure(model_task);

        proto_task->set_name(task.name());
        proto_task->set_label(task.label());
        proto_task->set_prior(task.prior());
        proto_task->set_date(task.date());
        proto_task->set_completed(task.completed());
    }

    return Status::OK;
}