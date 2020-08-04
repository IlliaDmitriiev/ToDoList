//
// Created by illia.dmitriiev on 7/27/2020.
//

#ifndef TODOLIST_FULLTASK_H
#define TODOLIST_FULLTASK_H

#include "Task.h"
#include "IDGenerator.h"
#include <memory>
#include <unordered_map>

class FullTask {

public:
    static FullTask create(const TaskID& id, const Task &task);

public:
    void addSubtask( const std::weak_ptr<FullTask>& ft);
    void deleteSubtask(TaskID id);

public:
    const Task &getTask() const;
    const TaskID &getId() const;
    const TaskID &getParent() const;
    std::unordered_map<TaskID, std::weak_ptr<FullTask>,
            TaskID::Hasher, TaskID::Comparator>& getSubTasks();
public:
    void setParent(TaskID id);

private:
    FullTask(TaskID ID, const Task &t);

private:
    TaskID id_;
    TaskID parent_;
    Task task_;
    std::unordered_map<TaskID, std::weak_ptr<FullTask>,
            TaskID::Hasher, TaskID::Comparator> subTasks_;
};

#endif //TODOLIST_FULLTASK_H
