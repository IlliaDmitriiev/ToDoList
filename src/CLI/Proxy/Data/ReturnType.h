//
// Created by ilya on 31.10.2020.
//

#ifndef TODOLIST_RETURNTYPE_H
#define TODOLIST_RETURNTYPE_H

#include "TaskID.h"
#include <string>
#include <optional>

/*
 * Structures containing info about the result of executing service request.
 *
 * @author Ilya Dmitriev
 */
enum class ResultType{
    SUCCESS,
    FAILURE
};

struct AddTaskResult{
    ResultType result;
    std::optional<TaskID> id;
    std::string error_message;
};

struct RequstTaskResult{
    ResultType result;
    std::string error_message;
};

#endif //TODOLIST_RETURNTYPE_H
