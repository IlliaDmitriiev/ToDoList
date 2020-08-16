//
// Created by illia on 13.08.20.
//

#ifndef TODOLIST_RETURNTYPECREATOR_H
#define TODOLIST_RETURNTYPECREATOR_H

/*
 * Namespace which generates an object containing info
 * about the result of executing service request.
 *
 * @author Ilya Dmitriev
 */

namespace operation_result{
   /*
    * Creates result representing successful execution.
    *
    * @param:[TaskID]
    *
    * @return AddTaskResult instance with positive success status and given TaskID.
    */
   AddTaskResult TaskAddedSuccessful(const TaskID &id) {
        AddTaskResult outcome;
        outcome.result = ResultType::SUCCESS;
        outcome.id = id;
        outcome.error_message = "";
        return outcome;
   }
   /*
    * Creates result representing unsuccessful execution.
    *
    * @return AddTaskResult instance with negative status and given error message.
    */
   AddTaskResult TaskAddedUnsuccessful(const std::string &error_message) {
        AddTaskResult outcome;
        outcome.result = ResultType::FAILURE;
        outcome.id = std::nullopt;
        outcome.error_message = error_message;
        return outcome;
   }
   /*
    * Creates result representing successful execution.
    *
    * @return RequstTaskResult instance with positive success status and null error message.
    */
   RequstTaskResult TaskRequestedSuccessful() {
        RequstTaskResult outcome;
        outcome.result = ResultType::SUCCESS;
        outcome.error_message = "";
        return outcome;
   }
   /*
    * Creates result representing unsuccessful execution.
    *
    * @return RequestTaskResult instance with negative status and given error message.
    */
   RequstTaskResult TaskRequestedUnsuccessful(const std::string &error_message) {
        RequstTaskResult outcome;
        outcome.result = ResultType::FAILURE;;
        outcome.error_message = error_message;
        return outcome;
   }

}

#endif //TODOLIST_RETURNTYPECREATOR_H
