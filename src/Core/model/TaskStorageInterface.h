//
// Created by illia on 14.08.20.
//

#ifndef TODOLIST_TASKSTORAGEINTERFACE_H
#define TODOLIST_TASKSTORAGEINTERFACE_H

#include "FullTask.h"
#include <unordered_map>
#include <vector>
#include <optional>

/*
 * Class which holds tasks
 *
 * @author: Ilya Dmitriev
 */
class TaskStorageInterface {

public:
    /*
     * adds task to storage
     *
     * @param: task link
     *
     * @return true if operation is successful, otherwise false
     */
    virtual bool addTask(std::shared_ptr<FullTask> sft) = 0;
    /*
     * gets task from storage
     *
     * @param: [TaskID] needs to find task
     *
     * @return task link if such link exists otherwise nullopt.
     */
    virtual std::optional<std::weak_ptr<FullTask>> getTask(TaskID id)= 0;
    /*
     * deletes sybtask of Parent task
     *
     * @param: parentID needs to find parent
     * @param: taskID needs to find subtask of parent task
     *
     * @return false if function can't find parent task or subtask of parent
     * @return true if operation is successful
     */
    virtual bool deleteSubtaskInParent(TaskID ParentID, TaskID taskID)= 0;
     /*
     * deletes sybtask of Parent task
     *
     * @param: taskID needs to find task
     *
     * @return false if function can't find task
     * @return true if operation is successful
     */
    virtual bool deleteTask(TaskID id)= 0;
    virtual ~TaskStorageInterface() = default;

};

#endif //TODOLIST_TASKSTORAGEINTERFACE_H
