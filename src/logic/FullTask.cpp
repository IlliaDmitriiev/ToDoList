//
// Created by illia.dmitriiev on 7/27/2020.
//

#include "FullTask.h"

FullTask FullTask::create(const TaskID& id, const Task &task){
    FullTask ft(id, task);
    return ft;
}


void FullTask::addSubtask(TaskID subtaskID, std::weak_ptr<FullTask> ft){
    subtasks_.insert({subtaskID, ft});
}

void FullTask::removeSubtasks( std::unordered_map<TaskID, std::shared_ptr<FullTask>, TaskID::Hasher, TaskID::Comparator> &allTasks){

    for (auto i: subtasks_){
        if (!i.second.expired())
            i.second.lock()->removeSubtasks(allTasks);

        allTasks[i.first].reset();
        i.second.reset();
        allTasks.erase(i.first);
    }

    subtasks_.clear();
}

const Task &FullTask::getTask() const {
    return task_;
}

FullTask::FullTask(TaskID ID, const Task &t) : id_(ID), task_(t) {}

const TaskID &FullTask::getId() const {
    return id_;
}

