//
// Created by illia.dmitriiev on 8/11/2020.
//

#ifndef TODOLIST_CREATOR_H
#define TODOLIST_CREATOR_H

#include "TaskService.h"

namespace Creator {

    static TaskService createService() {
        auto viewByPriority = std::make_unique<ViewByPriority>();
        auto viewByDate = std::make_unique<ViewByDate>();
        return TaskService(std::move(viewByPriority), std::move(viewByDate));
    }

    static AddTaskResult createAddTaskResult(const ResultType &result,  const std::optional<TaskID> &id, const std::string &error_message){
        AddTaskResult outcome;
        outcome.result = result;
        outcome.id = id;
        outcome.error_message = error_message;
        return outcome;
    }

    static RequstTaskResult createRequestTaskResult(const ResultType &result, const std::string &error_message){
        RequstTaskResult outcome;
        outcome.result = result;
        outcome.error_message = error_message;
        return outcome;
    }

}
#endif //TODOLIST_CREATOR_H
