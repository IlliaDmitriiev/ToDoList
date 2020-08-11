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

        for( auto &i: Node->second.at(Task::Priority::First))
            v.push_back(i.second);
        for( auto &i: Node->second.at(Task::Priority::Second))
            v.push_back(i.second);
        for( auto &i: Node->second.at(Task::Priority::Third))
            v.push_back(i.second);
        for( auto &i: Node->second.at(Task::Priority::None))
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

            for( auto &i: NeedData->second.at(Task::Priority::First))
                v.push_back(i.second);
            for( auto &i: NeedData->second.at(Task::Priority::Second))
                v.push_back(i.second);
            for( auto &i: NeedData->second.at(Task::Priority::Third))
                v.push_back(i.second);
            for( auto &i: NeedData->second.at(Task::Priority::None))
                v.push_back(i.second);
        }
    }
    return v;
}

void ViewByDate::addTask(const std::weak_ptr<FullTask>& ft){
    Date date = ft.lock()->getTask().getDate();
    auto foundDate = map_.find(date);

    if (foundDate != map_.end()) {
        Task::Priority priority = ft.lock()->getTask().getPrior();
        foundDate->second[priority][ft.lock()->getId()] = ft;
    }
    else {
        std::map<Task::Priority, std::map<TaskID, std::weak_ptr<FullTask>, TaskID::MapComparator> > map;
        std::map<TaskID, std::weak_ptr<FullTask>, TaskID::MapComparator> EmptyMap;

        map[Task::Priority::First] = EmptyMap;
        map[Task::Priority::Second] = EmptyMap;
        map[Task::Priority::Third]= EmptyMap;
        map[Task::Priority::None]= EmptyMap;

        Task::Priority priority = ft.lock()->getTask().getPrior();
        map[priority][ft.lock()->getId()] = ft;

        map_.insert({date, map});
    }
}

bool ViewByDate::deleteTask(const std::weak_ptr<FullTask>& ft){
    Date date = ft.lock()->getTask().getDate();
    Task::Priority priority = ft.lock()->getTask().getPrior();
    TaskID id = ft.lock()->getId();

    return map_[date][priority].erase(id);

}