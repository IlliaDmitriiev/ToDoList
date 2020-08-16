//
// Created by illia.dmitriiev on 7/27/2020.
//

#ifndef TODOLIST_TASKSERVICE_H
#define TODOLIST_TASKSERVICE_H

#include "logic/IDGenerator.h"
#include "logic/ViewInterface.h"
#include "logic/ViewByPriority.h"
#include "logic/ViewByDate.h"
#include "logic/TaskConvertor.h"
#include "model/TaskStorage.h"
#include "ReturnType.h"

/*
 *  Enter point to the program.
 *
 *  All requests to the system starts here.
 *
 *  @author: Ilya Dmitriev
 */

class TaskService {

public:
    TaskService(
        std::unique_ptr<IDGeneratorInterface> generator,
        std::unique_ptr<ViewInterface> byPriority,
        std::unique_ptr<ViewInterface> byDate,
        std::unique_ptr<TaskStorageInterface> storage)
    :
    generator_(std::move(generator)),
    byPriority_(std::move(byPriority)),
    byDate_(std::move(byDate)),
    storage_(std::move(storage))
    {}

public:
    /*
     * Adds given task to system.
     *
     * @param: TaskDTO without TaskID.
     *
     * @return object containing id of new created task or info about possible errors.
     */
    AddTaskResult addTask(const TaskDTO &taskDto);
    /*
     * Adds subtask to the task with given TaskID.
     *
     * @param: [TaskID] It needs to add subtask to task by this id.
     * @param: TaskDTO without TaskID.
     *
     * @return object containing id of new created task or info about possible errors.
     */
    AddTaskResult addSubtask(TaskID taskID, const TaskDTO &subtask);
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
    RequstTaskResult deleteTask(TaskID id);
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
    RequstTaskResult complete(TaskID id);
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
    RequstTaskResult postponeTask(TaskID id, boost::gregorian::date new_date);

public:
    /*
     * Gives all tasks already sorted by priority.
     *
     * @return vector of TaskDTO
     *
     * @note if there isn't any required task, function will return empty vector
     */
    std::vector<TaskDTO> getAllTasksByPriority();
    /*
     * Gives all tasks for today already sorted by priority.
     *
     * @return vector of TaskDTO
     *
     * @note if there isn't any required task, function will return empty vector
     */
    std::vector<TaskDTO> getTasksForToday();
    /*
     * Gives all tasks for this week already sorted by priority.
     *
     * @return vector of TaskDTO
     *
     * @note if there isn't any required task, function will return empty vector
     */
    std::vector<TaskDTO> getTasksForWeek();
    /*
     * Gives task with given id if such exists in system.
     *
     * @param: [taskID].
     *
     * @return taskDTO if such task exists otherwise nullopt.
     */
    std::optional<TaskDTO> getTask(TaskID id);

private:
    /*
     * Deletes task from system.
     *
     * @param: [task link].
     *
     * @return true if removing is successful otherwise false
     */
    bool removeTask(const std::weak_ptr<FullTask> &task);

private:
    std::unique_ptr<IDGeneratorInterface> generator_;
    std::unique_ptr<TaskStorageInterface> storage_;
    std::unique_ptr<ViewInterface> byPriority_;
    std::unique_ptr<ViewInterface> byDate_;
};

#endif //TODOLIST_TASKSERVICE_H
