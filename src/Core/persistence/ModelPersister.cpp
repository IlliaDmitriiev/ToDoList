//
// Created by ilya on 04.10.2020.
//

#include "ModelPersister.h"
#include "PriorityConvertor.h"
#include "ProtoTaskConvertor.h"

bool ModelPersister::save() {

    Storage storage;

    for (const auto& task : model_.getAllTasks()) {
        if (!model_.getParent(task.getId())) {
            TaskEntity* task_message = storage.add_tasks();
            if (!saveSubtasks(task, task_message)) {
                return false;
            }
        }
    }
    return storage.SerializeToOstream(&file_);
}

bool ModelPersister::saveSubtasks(const ModelTaskDTO& task, TaskEntity* message) {
    auto proto_task = ProtoTaskConvertor::transferToTaskStructure(task);
    message->set_allocated_task(new TaskStructure(proto_task));

    for (const auto& subtask : model_.getSubtasks(task.getId())) {

        TaskEntity* subtask_message = message->add_subtasks();
        if (!saveSubtasks(subtask, subtask_message)) {
            return false;
        }

    }
    return true;
}

bool ModelPersister::load() {
    Storage storage;
    if (!storage.ParseFromIstream(&file_)) {
        return false;
    }

    for (const TaskEntity& task_load : storage.tasks()) {

        ModelTaskDTO task = ProtoTaskConvertor::transferToModelTask(task_load.task());
        auto result = model_.addTask(task);

        if (ResultType::FAILURE == result.result) {
            return false;
        }
        if (!loadSubtasks(result.id.value(), task_load)) {
            return false;
        }
    }
    return true;
}

bool ModelPersister::loadSubtasks(TaskID id, const TaskEntity& message) {
    for (const TaskEntity& subtask_load : message.subtasks()) {

        ModelTaskDTO subtask = ProtoTaskConvertor::transferToModelTask(subtask_load.task());
        auto result = model_.addSubtask(id, subtask);

        if (ResultType::FAILURE == result.result) {
            return false;
        }

        TaskID subtaskID = result.id.value();
        if (!loadSubtasks(subtaskID, subtask_load)) {
            return false;
        }
    }

    return true;
}