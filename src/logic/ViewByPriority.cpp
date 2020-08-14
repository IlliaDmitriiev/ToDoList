//
// Created by Илля on 31.07.2020.
//

#include "ViewByPriority.h"

ViewByPriority::ViewByPriority(){
    std::map<TaskID, std::weak_ptr<FullTask>, TaskID::MapComparator> mp;
    map_[TaskPriority::First] = mp;
    map_[TaskPriority::Second] = mp;
    map_[TaskPriority::Third]= mp;
    map_[TaskPriority::None]= mp;
}

std::vector<std::weak_ptr<FullTask>> ViewByPriority::getAllTasksByPrior(){
    std::vector<std::weak_ptr<FullTask>> v;

    for(auto &i: map_.at(TaskPriority::First))
        v.push_back(i.second);
    for(auto &i: map_.at(TaskPriority::Second))
        v.push_back(i.second);
    for(auto &i: map_.at(TaskPriority::Third))
        v.push_back(i.second);
    for(auto &i: map_.at(TaskPriority::None))
        v.push_back(i.second);

    return v;
}

std::vector<std::weak_ptr<FullTask>> ViewByPriority::getTasksForToday(BoostDate date) {
    std::vector<std::weak_ptr<FullTask>> v;
    return v;
}

std::vector<std::weak_ptr<FullTask>> ViewByPriority::getTasksForWeek(BoostDate date){
    std::vector<std::weak_ptr<FullTask>> v;
    return v;
}

bool ViewByPriority::addTask(const std::weak_ptr<FullTask>& cur){
    TaskPriority priority = cur.lock()->getTask().getPriority();
    map_[priority][cur.lock()->getId()] = cur;
    return true;
}

bool ViewByPriority::deleteTask(const std::weak_ptr<FullTask>& cur){
    TaskPriority priority = cur.lock()->getTask().getPriority();
    TaskID id = cur.lock()->getId();
    return map_[priority].erase(id);
}
