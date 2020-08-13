//
// Created by illia on 13.08.20.
//

#ifndef TODOLIST_RETURNTYPECREATOR_H
#define TODOLIST_RETURNTYPECREATOR_H

namespace return_type{

   AddTaskResult createAddTaskResult(const ResultType &result, const std::optional <TaskID> &id, const std::string &error_message) {
        AddTaskResult outcome;
        outcome.result = result;
        outcome.id = id;
        outcome.error_message = error_message;
        return outcome;
   }

   RequstTaskResult createRequestTaskResult(const ResultType &result, const std::string &error_message) {
        RequstTaskResult outcome;
        outcome.result = result;
        outcome.error_message = error_message;
        return outcome;
   }

}

#endif //TODOLIST_RETURNTYPECREATOR_H
