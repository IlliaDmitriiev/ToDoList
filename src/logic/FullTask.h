//
// Created by illia.dmitriiev on 7/27/2020.
//

#ifndef TODOLIST_FULLTASK_H
#define TODOLIST_FULLTASK_H

#include "Task.h"
#include "IDGenerator.h"
#include <memory>
#include <vector>

class FullTask {

public:
    static FullTask create(const TaskID& id, const Task &task);

public:
    void addSubtask( std::weak_ptr<FullTask> ft);

public:
    const Task &getTask() const;
    const TaskID &getId() const;

private:
    FullTask(TaskID ID, const Task &t);

private:
    TaskID id_;
    Task task_;
    std::vector<std::weak_ptr<FullTask>> subtask_;
};

#endif //TODOLIST_FULLTASK_H
