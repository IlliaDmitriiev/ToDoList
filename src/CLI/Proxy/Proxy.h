//
// Created by ilya on 31.10.2020.
//

#ifndef TODOLIST_PROXY_H
#define TODOLIST_PROXY_H

#include "CLI/Proxy/Data/TaskDTO.h"
#include "CLI/Proxy/Data/ReturnType.h"
#include "CLI/Utils/Creators/ReturnTypeCreator.h"

class Proxy{

public:
    /*
     * Adds given task to system.
     *
     * @param: ServiceTaskDTO without TaskID.
     *
     * @return object containing id of new created task or info about possible errors.
     */
    virtual AddTaskResult addTask(const TaskDTO &taskDto) = 0;
    /*
     * Adds subtask to the task with given TaskID.
     *
     * @param: [TaskID] It needs to add subtask to task by this id.
     * @param: ServiceTaskDTO without TaskID.
     *
     * @return object containing id of new created task or info about possible errors.
     */
    virtual AddTaskResult addSubtask(TaskID taskID, const TaskDTO &subtask) = 0;
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
    virtual RequstTaskResult editTask(TaskID id, const TaskDTO &subtask) = 0;

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
    virtual std::vector<TaskDTO> getSubtasks(TaskID id) = 0;
    /*
     * Gives all tasks already sorted by priority.
     *
     * @return vector of ServiceTaskDTO
     *
     * @note if there isn't any required task, function will return empty vector
     */
    virtual std::vector<TaskDTO> getAllTasksByPriority() = 0;
    /*
     * Gives all tasks for today already sorted by priority.
     *
     * @return vector of ServiceTaskDTO
     *
     * @note if there isn't any required task, function will return empty vector
     */
    virtual std::vector<TaskDTO> getTasksForToday() = 0;
    /*
     * Gives all tasks for this week already sorted by priority.
     *
     * @return vector of ServiceTaskDTO
     *
     * @note if there isn't any required task, function will return empty vector
     */
    virtual std::vector<TaskDTO> getTasksForWeek() = 0;
    /*
     * Gives task with given id if such exists in system.
     *
     * @param: [taskID].
     *
     * @return taskDTO if such task exists otherwise nullopt.
     */
    virtual std::optional<TaskDTO> getTask(TaskID id) = 0;
    /*
     * saves all tasks
     *
     * @parameters [string filename]
     *
     * @return object containing info about possible error occurred
     * or info that operation is successful.
     */
    virtual RequstTaskResult save(const std::string&) = 0;
    /*
     * loads all tasks in system
     *
     * @parameters [string filename]
     *
     * @return object containing info about possible error occurred
     * or info that operation is successful.
     */
    virtual RequstTaskResult load(const std::string&) = 0;

    virtual ~Proxy() = default;

};

#endif //TODOLIST_PROXY_H
