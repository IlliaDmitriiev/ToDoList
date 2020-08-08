//
// Created by Илля on 08.08.2020.
//

#include "TaskCreationResult.h"

TaskCreationResult TaskCreationResult::success(const TaskID &id) {
    return TaskCreationResult(std::make_optional(id), std::nullopt);
}

TaskCreationResult TaskCreationResult::taskNotFound() {
    return TaskCreationResult(std::nullopt, std::nullopt);
}

TaskCreationResult TaskCreationResult::error(const std::string &message) {
    return TaskCreationResult(std::nullopt, message);
}

TaskCreationResult::TaskCreationResult(const std::optional<TaskID> &taskId,
        const std::optional<std::string> &errorMessage) : taskID(taskId),
        errorMessage(errorMessage) {}

std::optional<TaskID> TaskCreationResult::getTaskID(){
    return taskID;
}

std::optional<std::string> TaskCreationResult::getErrorMessage(){
    return errorMessage;
}

