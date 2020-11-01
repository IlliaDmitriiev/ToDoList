//
// Created by illia.dmitriiev on 7/27/2020.
//

#ifndef TODOLIST_FULLTASK_H
#define TODOLIST_FULLTASK_H

#include "Task.h"
#include "Core/model/logic/IDGenerator.h"
#include <memory>
#include <unordered_map>
#include <vector>
/*
 * class-holder of tasks
 *
 * @see Task
 *
 * @author:Ilya Dmitriev
 */
class FullTask {

public:
    static FullTask create(const TaskID& id, const Task &task);

private:
    FullTask(TaskID ID, const Task &t);

public:
    void addSubtask( const std::weak_ptr<FullTask>& ft);
    void deleteSubtask(TaskID id);
    void setParent(TaskID id);
    /*
     * set status complete true
     *
     * @note: All subtasks will be completed recursively.
     */
    void complete();
    /*
     * Changing task date to the given.
     *
     * @param: [date] It needs to change task date with this date.
     *
     * @note: All subtasks will NOT be postponed recursively.
     */
    void postpone(boost::gregorian::date new_date);
    /*
     * Changing task to the given.
     *
     * @param: [Task] It needs to change task with a new one.
     */
    void change(Task);

public:
    const Task &getTask() const;
    const TaskID &getId() const;
    const TaskID &getParent() const;
    const bool isComplete() const;
    std::vector<TaskID> getSubtasks() const;

private:
    TaskID id_;
    TaskID parent_;
    Task task_;
    bool complete_;
    std::unordered_map<TaskID, std::weak_ptr<FullTask>,
            TaskID::Hasher, TaskID::Comparator> subTasks_;
};

#endif //TODOLIST_FULLTASK_H
