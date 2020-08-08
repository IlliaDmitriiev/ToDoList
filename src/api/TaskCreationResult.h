//
// Created by Илля on 08.08.2020.
//

#ifndef TODOLIST_TASKCREATIONRESULT_H
#define TODOLIST_TASKCREATIONRESULT_H

#include "model/TaskID.h"
#include <optional>
#include <string>

class TaskCreationResult {

public:
    static TaskCreationResult success(const TaskID &id_created);
    static TaskCreationResult error(const std::string& message);
    static TaskCreationResult taskNotFound();

public:
    std::optional<TaskID> getTaskID();
    std::optional<std::string> getErrorMessage();

private:
    TaskCreationResult(const std::optional<TaskID> &taskId, const std::optional<std::string> &errorMessage);

private:
    std::optional<TaskID> taskID;
    std::optional<std::string> errorMessage;

};


#endif //TODOLIST_TASKCREATIONRESULT_H
