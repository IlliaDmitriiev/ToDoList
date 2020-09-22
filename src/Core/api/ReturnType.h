//
// Created by Илля on 08.08.2020.
//

#ifndef TODOLIST_RETURNTYPE_H
#define TODOLIST_RETURNTYPE_H

#include "TaskID.h"
#include <string>

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
