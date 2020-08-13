//
// Created by illia on 13.08.20.
//

#ifndef TODOLIST_RETURNTYPECREATOR_H
#define TODOLIST_RETURNTYPECREATOR_H

namespace operation_result{

   AddTaskResult TaskAddedSuccessful(const std::optional <TaskID> &id) {
        AddTaskResult outcome;
        outcome.result = ResultType::SUCCESS;
        outcome.id = id;
        outcome.error_message = "";
        return outcome;
   }
   AddTaskResult TaskAddedUnsuccessful(const std::string &error_message) {
        AddTaskResult outcome;
        outcome.result = ResultType::FAILURE;
        outcome.id = std::nullopt;
        outcome.error_message = error_message;
        return outcome;
   }

   RequstTaskResult TaskRequestedSuccessful() {
        RequstTaskResult outcome;
        outcome.result = ResultType::SUCCESS;
        outcome.error_message = "";
        return outcome;
   }

   RequstTaskResult TaskRequestedUnsuccessful(const std::string &error_message) {
        RequstTaskResult outcome;
        outcome.result = ResultType::FAILURE;;
        outcome.error_message = error_message;
        return outcome;
   }

}

#endif //TODOLIST_RETURNTYPECREATOR_H
