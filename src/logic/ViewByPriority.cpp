//
// Created by Илля on 31.07.2020.
//

#include "ViewByPriority.h"

ViewByPriority::ViewByPriority(){
    std::map<TaskID, std::weak_ptr<FullTask>, TaskID::MapComparator> mp;
    map_[Task::Priority::First] = mp;
    map_[Task::Priority::Second] = mp;
    map_[Task::Priority::Third]= mp;
    map_[Task::Priority::None]= mp;
}

std::vector<std::weak_ptr<FullTask>> ViewByPriority::getAllTasksByPrior(){
    std::vector<std::weak_ptr<FullTask>> v;

    for(auto &i: map_.at(Task::Priority::First))
        v.push_back(i.second);
    for(auto &i: map_.at(Task::Priority::Second))
        v.push_back(i.second);
    for(auto &i: map_.at(Task::Priority::Third))
        v.push_back(i.second);
    for(auto &i: map_.at(Task::Priority::None))
        v.push_back(i.second);

    return v;
}

std::vector<std::weak_ptr<FullTask>> ViewByPriority::getTasksForToday(Date date) {
    std::vector<std::weak_ptr<FullTask>> v;
    return v;
}

std::vector<std::weak_ptr<FullTask>> ViewByPriority::getTasksForWeek(Date date){
    std::vector<std::weak_ptr<FullTask>> v;
    return v;
}

void ViewByPriority::addTask(const std::weak_ptr<FullTask>& cur){
    Task::Priority priority = cur.lock()->getTask().getPrior();
    map_[priority][cur.lock()->getId()] = cur;

}

bool ViewByPriority::deleteTask(const std::weak_ptr<FullTask>& cur){
    Task::Priority priority = cur.lock()->getTask().getPrior();
    TaskID id = cur.lock()->getId();
    return map_[priority].erase(id);
}
