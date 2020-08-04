//
// Created by illia.dmitriiev on 7/27/2020.
//

#include "FullTask.h"

FullTask FullTask::create(const TaskID& id, const Task &task){
    FullTask ft(id, task);
    return ft;
}

void FullTask::addSubtask( const std::weak_ptr<FullTask>& ft){
    subTasks_.insert({ft.lock()->getId(), ft});
    ft.lock()->setParent(id_);
}

void FullTask::deleteSubtask(TaskID id){
    subTasks_.erase(id);
}

void FullTask::setParent(TaskID id){
    parent_ = id;
}

const Task &FullTask::getTask() const {
    return task_;
}

FullTask::FullTask(TaskID id, const Task &t) : id_(id), task_(t), parent_(id){}

const TaskID &FullTask::getId() const {
    return id_;
}

const TaskID &FullTask::getParent() const {
    return parent_;
}

std::unordered_map<TaskID, std::weak_ptr<FullTask>,
        TaskID::Hasher, TaskID::Comparator >& FullTask::getSubTasks(){
    return subTasks_;
}

