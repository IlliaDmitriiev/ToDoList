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
    static FullTask create(IDGenerator &generator, const Task &task);
public:
    static void Print(const std::weak_ptr<FullTask> &task);

public:
    void addSubtask(TaskID subtaskID, std::weak_ptr<FullTask> ft);
    void removeSubtasks( std::unordered_map<TaskID, std::shared_ptr<FullTask>, TaskID::Hasher, TaskID::Comparator> &allTasks);

public:
    const Task &getTask() const;
    const TaskID &getId() const;

private:
    FullTask(TaskID ID, const Task &t);

private:
    TaskID id_;
    Task task_;
    std::unordered_map<TaskID, std::weak_ptr<FullTask>, TaskID::Hasher, TaskID::Comparator> subtasks_;
};

#endif //TODOLIST_FULLTASK_H
