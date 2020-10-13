//
// Created by illia on 17.08.20.
//

#ifndef TODOLIST_TASKSERVICEINTERFACE_H
#define TODOLIST_TASKSERVICEINTERFACE_H


#include "ReturnType.h"
#include "Core/model/DataInterface.h"
#include "Core/utils/TaskConvertor.h"

/*
 *  Enter point to the Core.
 *
 *  All requests to the system starts executing here.
 *
 *  @author: Ilya Dmitriev
 */

class TaskServiceInterface{

public:
    /*
     * Adds given task to system.
     *
     * @param: ServiceTaskDTO without TaskID.
     *
     * @return object containing id of new created task or info about possible errors.
     */
    virtual AddTaskResult addTask(const ServiceTaskDTO &taskDto) = 0;
    /*
     * Adds subtask to the task with given TaskID.
     *
     * @param: [TaskID] It needs to add subtask to task by this id.
     * @param: ServiceTaskDTO without TaskID.
     *
     * @return object containing id of new created task or info about possible errors.
     */
    virtual AddTaskResult addSubtask(TaskID taskID, const ServiceTaskDTO &subtask) = 0;
    /*
     * Deletes task from system.
     *
     * @param: [TaskID] It needs to delete task by this id.
     *
     * @return object containing info about possible error occurred
     * or info that operation is successful.
     *
     * @note: All subtasks will be deleted recursively.
     */
    virtual RequstTaskResult deleteTask(TaskID id) = 0;
    /*
     * Completes task.
     *
     * @param: [TaskID] It needs to complete task by this id.
     *
     * @return object containing info about possible error occurred
     * or info that operation is successful.
     *
     * @note: All subtasks will be completed recursively.
     */
    virtual RequstTaskResult complete(TaskID id) = 0;
    /*
     * Changing task date to the given.
     *
     * @param: [TaskID] It needs to find task by this id.
     * @param: [date] It needs to change task date with this date.
     *
     * @return object containing info about possible error occurred
     * or info that operation is successful.
     *
     * @note: All subtasks will NOT be postponed recursively.
     */
    virtual RequstTaskResult postponeTask(TaskID id, boost::gregorian::date new_date) = 0;
    /*
     * Changing task to the given.
     *
     * @param: [TaskID] It needs to find task by this id.
     * @param: [ServiceTaskDTO] It needs to change task with a new one.
     *
     * @return object containing info about possible error occurred
     * or info that operation is successful.
     *
     * @note: All subtasks will NOT be edited recursively.
     */
    virtual RequstTaskResult editTask(TaskID id, const ServiceTaskDTO &subtask) = 0;

public:
    /*
     * Gives all subtasks by given id.
     *
     * @param: [TaskID] It needs to find task by this id.
     *
     * @return vector of ServiceTaskDTO
     *
     * @note if there isn't any required task, function will return empty vector
     */
    virtual std::vector<ServiceTaskDTO> getSubtasks(TaskID id) = 0;
    /*
     * Gives all tasks already sorted by priority.
     *
     * @return vector of ServiceTaskDTO
     *
     * @note if there isn't any required task, function will return empty vector
     */
    virtual std::vector<ServiceTaskDTO> getAllTasksByPriority() = 0;
    /*
     * Gives all tasks for today already sorted by priority.
     *
     * @return vector of ServiceTaskDTO
     *
     * @note if there isn't any required task, function will return empty vector
     */
    virtual std::vector<ServiceTaskDTO> getTasksForToday() = 0;
    /*
     * Gives all tasks for this week already sorted by priority.
     *
     * @return vector of ServiceTaskDTO
     *
     * @note if there isn't any required task, function will return empty vector
     */
    virtual std::vector<ServiceTaskDTO> getTasksForWeek() = 0;
    /*
     * Gives task with given id if such exists in system.
     *
     * @param: [taskID].
     *
     * @return taskDTO if such task exists otherwise nullopt.
     */
    virtual std::optional<ServiceTaskDTO> getTask(TaskID id) = 0;
    /*
     * saves all tasks
     *
     * @return object containing info about possible error occurred
     * or info that operation is successful.
     */
    virtual RequstTaskResult save(const std::string&) = 0;
    /*
     * loads all tasks in system
     *
     * @return object containing info about possible error occurred
     * or info that operation is successful.
     */
    virtual RequstTaskResult load(const std::string&) = 0;

    virtual ~TaskServiceInterface() = default;

};

#endif //TODOLIST_TASKSERVICEINTERFACE_H
