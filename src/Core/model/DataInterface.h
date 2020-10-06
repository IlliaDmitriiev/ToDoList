//
// Created by ilya on 24.09.2020.
//

#ifndef TODOLIST_DATAINTERFACE_H
#define TODOLIST_DATAINTERFACE_H

#include "TaskStorageInterface.h"
#include "Core/logic/ViewInterface.h"
#include "Core/utils/ReturnTypeCreator.h"
#include "Core/utils/ModelTaskConvertor.h"
/*
 * Model api to manage data.
 *
 * @author: Ilya Dmitriev
 */
class DataInterface{

public:
   /*
    * Adds given task to system.
    *
    * @param: ModelTaskDTO without TaskID.
    *
    * @return object containing id of new created task or info about possible errors.
    */
    virtual AddTaskResult addTask(const ModelTaskDTO &taskDto) = 0;
    /* bool removeTask(const std::weak_ptr<FullTask> &task) override;
     * Adds subtask to the task with given TaskID.
     *
     * @param: [TaskID] It needs to add subtask to task by this id.
     * @param: ModelTaskDTO without TaskID.
     *
     * @return object containing id of new created task or info about possible errors.
     */
    virtual AddTaskResult addSubtask(TaskID taskID, const ModelTaskDTO &subtask) = 0;
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
     * Changing task to the given.
     *
     * @param: [TaskID] It needs to find task by this id.
     * @param: [ModelTaskDTO] It needs to change task with a new one.
     *
     * @return object containing info about possible error occurred
     * or info that operation is successful.
     *
     * @note: All subtasks will NOT be edited recursively.
     */
    virtual RequstTaskResult editTask(TaskID id, const ModelTaskDTO &subtask) = 0;

public:
    /*
     * Gives all subtasks by given id.
     *
     * @param: [TaskID] It needs to find task by this id.
     *
     * @return vector of ModelTaskDTO
     *
     * @note if there isn't any required task, function will return empty vector
     */
    virtual std::vector<ModelTaskDTO> getSubtasks(TaskID id) = 0;
    /*
     * Returns all task
     *
     * @return vector of ModelTaskDTO
     *
     * @note if there isn't any required task, function will return empty vector
     */
    virtual std::vector<ModelTaskDTO> getAllTasks() = 0;
    /*
     * Gives task with given id if such exists in system.
     *
     * @param: [taskID].
     *
     * @return taskDTO if such task exists otherwise nullopt.
     */
    virtual std::optional<ModelTaskDTO> getTask(TaskID id) = 0;
    /*
    * Gives id of parent task.
    *
    * @param: [taskID].
    *
    * @return taskID if parent exists otherwise nullopt.
    */
    virtual std::optional<TaskID> getParent(TaskID id) = 0;
    /*
     * Gives all tasks already sorted by priority.
     *
     * @return vector of ModelTaskDTO
     *
     * @note if there isn't any required task, function will return empty vector
     */
    virtual std::vector<ModelTaskDTO> getAllTasksByPriority() = 0;
    /*
     * Gives all tasks for today already sorted by priority.
     *
     * @return vector of ModelTaskDTO
     *
     * @note if there isn't any required task, function will return empty vector
     */
    virtual std::vector<ModelTaskDTO> getTasksForToday() = 0;
    /*
     * Gives all tasks for this week already sorted by priority.
     *
     * @return vector of ModelTaskDTO
     *
     * @note if there isn't any required task, function will return empty vector
     */
    virtual std::vector<ModelTaskDTO> getTasksForWeek() = 0;

private:
    /*
     * Deletes task from system.
     *
     * @param: [task link].
     *
     * @return true if removing is successful otherwise false
     */
    virtual bool removeTask(const std::weak_ptr<FullTask> &task) = 0;

public:
    ~DataInterface() = default;
};

#endif //TODOLIST_DATAINTERFACE_H
