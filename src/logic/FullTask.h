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
    static FullTask create(IDGenerator &generator, const Task &t);

public:
    void addSubtask(TaskID subtaskID, std::weak_ptr<FullTask> ft);
    void removeSubtasks( std::unordered_map<int, std::shared_ptr<FullTask> > &allTasks);

public:
    const Task &getTask() const;

private:
    FullTask(TaskID ID, const Task &t) : ID(ID), t(t) {}

private:
    TaskID ID;
    Task t;
    std::unordered_map<int, std::weak_ptr<FullTask> > subtasks;
};

#endif //TODOLIST_FULLTASK_H
