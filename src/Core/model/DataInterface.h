//
// Created by ilya on 24.09.2020.
//

#ifndef TODOLIST_DATAINTERFACE_H
#define TODOLIST_DATAINTERFACE_H

#include "TaskStorageInterface.h"
#include "Core/logic/ViewInterface.h"
#include "Core/api/ReturnTypeCreator.h"
#include "Core/logic/TaskConvertor.h"
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
    * @param: TaskDTO without TaskID.
    *
    * @return object containing id of new created task or info about possible errors.
    */
    virtual AddTaskResult addTask(const TaskDTO &taskDto) = 0;
    /* bool removeTask(const std::weak_ptr<FullTask> &task) override;
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
     * Changing task to the given.
     *
     * @param: [TaskID] It needs to find task by this id.
     * @param: [TaskDTO] It needs to change task with a new one.
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
     * @return vector of TaskDTO
     *
     * @note if there isn't any required task, function will return empty vector
     */
    virtual std::vector<TaskDTO> getSubtasks(TaskID id) = 0;
    /*
     * Returns all task
     *
     * @return vector of TaskDTO
     *
     * @note if there isn't any required task, function will return empty vector
     */
    virtual std::vector<TaskDTO> getAllTasks() = 0;
    /*
     * Gives task with given id if such exists in system.
     *
     * @param: [taskID].
     *
     * @return taskDTO if such task exists otherwise nullopt.
     */
    virtual std::optional<TaskDTO> getTask(TaskID id) = 0;
    /*
     * Gives an access to view by priority only for reading.
     *
     * @return ref to view
     *
     */
    virtual const ViewInterface& getByPriority() = 0;
    /*
     * Gives an access to view by date only for reading.
     *
     * @return ref to view
     *
     */
    virtual const ViewInterface& getByDate() = 0;

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
