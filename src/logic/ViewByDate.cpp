//
// Created by Илля on 30.07.2020.
//

#include "ViewByDate.h"

std::vector<std::weak_ptr<FullTask>> ViewByDate::getAllTasksByPrior() {
    std::vector<std::weak_ptr<FullTask>> v;
    return v;
}

std::vector<std::weak_ptr<FullTask>> ViewByDate::getTasksForToday(BoostDate date){

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

std::vector<std::weak_ptr<FullTask>>  ViewByDate::getTasksForWeek(BoostDate current_date){

    std::vector<std::weak_ptr<FullTask>> v;

    BoostDate date = current_date;
    int days_count = current_date.day_number();

    for(int i = 0; i<=6; ++i){
        BoostDate date1(days_count - i);
        if((int)date1.day_of_week() == 1) date = date1;
    }

    for (int j = 0; j<=6; ++j) {
        BoostDate date1(date.day_number() + j);
        const auto& NeedData = map_.find(date1);

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

bool ViewByDate::addTask(const std::weak_ptr<FullTask>& ft){
    BoostDate date = ft.lock()->getTask().getDate();
    auto foundDate = map_.find(date);

    if (foundDate != map_.end()) {
        TaskPriority priority = ft.lock()->getTask().getPriority();
        foundDate->second[priority][ft.lock()->getId()] = ft;
        return true;
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
        return true;
    }
}

bool ViewByDate::deleteTask(const std::weak_ptr<FullTask>& ft){
    BoostDate date = ft.lock()->getTask().getDate();
    TaskPriority priority = ft.lock()->getTask().getPriority();
    TaskID id = ft.lock()->getId();

    return map_[date][priority].erase(id);

}