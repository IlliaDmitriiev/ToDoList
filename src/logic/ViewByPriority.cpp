//
// Created by Илля on 31.07.2020.
//

#include "ViewByPriority.h"

std::vector<std::weak_ptr<FullTask>> ViewByPriority::getAllTasks(){
    std::vector<std::weak_ptr<FullTask>> v;

    for(auto i: map_[Task::Priority::First])
        v.push_back(i.second);
    for(auto i: map_[Task::Priority::Second])
        v.push_back(i.second);
    for(auto i: map_[Task::Priority::Third])
        v.push_back(i.second);
    for(auto i: map_[Task::Priority::None])
        v.push_back(i.second);

    return v;
}

void ViewByPriority::addTask(std::weak_ptr<FullTask> cur){
    Task::Priority priority = cur.lock()->getTask().getPrior();
    map_[priority][cur.lock()->getId()] = cur;

}

void ViewByPriority::deleteTask(Task::Priority priority, TaskID id){
    map_[priority].erase(id);
}

const std::map<Task::Priority, std::map<TaskID, std::weak_ptr<FullTask>, TaskID::MapComparator>> &
ViewByPriority::getMap() const {
    return map_;
}
