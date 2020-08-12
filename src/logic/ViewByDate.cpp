//
// Created by Илля on 30.07.2020.
//

#include "ViewByDate.h"

std::vector<std::weak_ptr<FullTask>> ViewByDate::getAllTasksByPrior() {
    std::vector<std::weak_ptr<FullTask>> v;
    return v;
}

std::vector<std::weak_ptr<FullTask>> ViewByDate::getTasksForToday(Date date){

    const auto& Node = map_.find(date);
    std::vector<std::weak_ptr<FullTask>> v;

    if(Node!=map_.end()){

        for( auto &i: Node->second.at(TaskPriority::First))
            v.push_back(i.second);
        for( auto &i: Node->second.at(TaskPriority::Second))
            v.push_back(i.second);
        for( auto &i: Node->second.at(TaskPriority::Third))
            v.push_back(i.second);
        for( auto &i: Node->second.at(TaskPriority::None))
            v.push_back(i.second);
    }
    return v;
}

std::vector<std::weak_ptr<FullTask>>  ViewByDate::getTasksForWeek(Date date){

    std::vector<std::weak_ptr<FullTask>> v;

    for (int j = 1; j<=7; ++j) {
        int WeekDay = date.getWday();
        if (WeekDay == 0) WeekDay = 7;
        date.moveWithinTheWeek(j - WeekDay);

        const auto& NeedData = map_.find(date);
        if (NeedData != map_.end()) {

            for( auto &i: NeedData->second.at(TaskPriority::First))
                v.push_back(i.second);
            for( auto &i: NeedData->second.at(TaskPriority::Second))
                v.push_back(i.second);
            for( auto &i: NeedData->second.at(TaskPriority::Third))
                v.push_back(i.second);
            for( auto &i: NeedData->second.at(TaskPriority::None))
                v.push_back(i.second);
        }
    }
    return v;
}

void ViewByDate::addTask(const std::weak_ptr<FullTask>& ft){
    Date date = ft.lock()->getTask().getDate();
    auto foundDate = map_.find(date);

    if (foundDate != map_.end()) {
        TaskPriority priority = ft.lock()->getTask().getPriority();
        foundDate->second[priority][ft.lock()->getId()] = ft;
    }
    else {
        std::map<TaskPriority, std::map<TaskID, std::weak_ptr<FullTask>, TaskID::MapComparator> > map;
        std::map<TaskID, std::weak_ptr<FullTask>, TaskID::MapComparator> EmptyMap;

        map[TaskPriority::First] = EmptyMap;
        map[TaskPriority::Second] = EmptyMap;
        map[TaskPriority::Third]= EmptyMap;
        map[TaskPriority::None]= EmptyMap;

        TaskPriority priority = ft.lock()->getTask().getPriority();
        map[priority][ft.lock()->getId()] = ft;

        map_.insert({date, map});
    }
}

bool ViewByDate::deleteTask(const std::weak_ptr<FullTask>& ft){
    Date date = ft.lock()->getTask().getDate();
    TaskPriority priority = ft.lock()->getTask().getPriority();
    TaskID id = ft.lock()->getId();

    return map_[date][priority].erase(id);

}