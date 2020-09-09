//
// Created by illia on 17.08.20.
//

#ifndef TODOLIST_TASKSERVICEINTERFACE_H
#define TODOLIST_TASKSERVICEINTERFACE_H

#include "Core/logic/IDGenerator.h"
#include "Core/logic/ViewInterface.h"
#include "Core/logic/ViewByPriority.h"
#include "Core/logic/ViewByDate.h"
#include "Core/logic/TaskConvertor.h"
#include "Core/model/TaskStorage.h"
#include "ReturnType.h"

/*
 *  Enter point to the program.
 *
 *  All requests to the system starts here.
 *
 *  @author: Ilya Dmitriev
 */

class TaskServiceInterface{

public:
    /*
     * Adds given task to system.
     *
     * @param: TaskDTO without TaskID.
     *
     * @return object containing id of new created task or info about possible errors.
     */
    virtual AddTaskResult addTask(const TaskDTO &taskDto) = 0;
    /*
     * Adds subtask to the task with given TaskID.
     *
     * @param: [TaskID] It needs to add subtask to task by this id.
     * @param: TaskDTO without TaskID.
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

public:
    /*
     * Gives all tasks already sorted by priority.
     *
     * @return vector of TaskDTO
     *
     * @note if there isn't any required task, function will return empty vector
     */
    virtual std::vector<TaskDTO> getAllTasksByPriority() = 0;
    /*
     * Gives all tasks for today already sorted by priority.
     *
     * @return vector of TaskDTO
     *
     * @note if there isn't any required task, function will return empty vector
     */
    virtual std::vector<TaskDTO> getTasksForToday() = 0;
    /*
     * Gives all tasks for this week already sorted by priority.
     *
     * @return vector of TaskDTO
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
    virtual ~TaskServiceInterface() = default;

private:
    /*
     * Deletes task from system.
     *
     * @param: [task link].
     *
     * @return true if removing is successful otherwise false
     */
    virtual bool removeTask(const std::weak_ptr<FullTask> &task) = 0;

};

#endif //TODOLIST_TASKSERVICEINTERFACE_H
