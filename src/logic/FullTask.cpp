//
// Created by illia.dmitriiev on 7/27/2020.
//

#include "FullTask.h"

FullTask FullTask::create(const TaskID& id, const Task &task){
    FullTask ft(id, task);
    return ft;
}

void FullTask::addSubtask( std::weak_ptr<FullTask> ft){
   subtask_.push_back(ft);
}

const Task &FullTask::getTask() const {
    return task_;
}

FullTask::FullTask(TaskID ID, const Task &t) : id_(ID), task_(t) {}

const TaskID &FullTask::getId() const {
    return id_;
}

