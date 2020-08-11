//
// Created by Илля on 30.07.2020.
//

#include "ViewByDate.h"


std::vector<std::weak_ptr<FullTask>> ViewByDate::getTasksForToday(Date date){

    auto Node = map_.find(date);
    std::vector<std::weak_ptr<FullTask>> v;

    if(Node!=map_.end()){
        auto PriorityMap = Node->second.getMap();

        for( auto i: PriorityMap[Task::Priority::First])
            v.push_back(i.second);
        for( auto i: PriorityMap[Task::Priority::Second])
            v.push_back(i.second);
        for( auto i: PriorityMap[Task::Priority::Third])
            v.push_back(i.second);
        for( auto i: PriorityMap[Task::Priority::None])
            v.push_back(i.second);
    }
    return v;
}

std::vector<std::weak_ptr<FullTask>>  ViewByDate::getTasksForWeek(Date date){

    std::vector<std::weak_ptr<FullTask>> v;

    for (int i = 1; i<=7; ++i) {
        int WeekDay = date.getWday();
        if (WeekDay == 0) WeekDay = 7;
        date.moveWithinTheWeek(i - WeekDay);

        auto NeedData = map_.find(date);
        if (NeedData != map_.end()) {
            auto PriorityMap = NeedData->second.getMap();

            for( auto i: PriorityMap[Task::Priority::First])
                v.push_back(i.second);
            for( auto i: PriorityMap[Task::Priority::Second])
                v.push_back(i.second);
            for( auto i: PriorityMap[Task::Priority::Third])
                v.push_back(i.second);
            for( auto i: PriorityMap[Task::Priority::None])
                v.push_back(i.second);
        }
    }
    return v;
}

void ViewByDate::addTask(const std::weak_ptr<FullTask>& ft){
    Date date = ft.lock()->getTask().getDate();
    auto foundDate = map_.find(date);

    if (foundDate != map_.end()) {
        foundDate->second.addTask(ft);
    }
    else {
        ViewByPriority map;
        map.addTask(ft);
        map_.insert({date, map});
    }
}

void ViewByDate::deleteTask(const std::weak_ptr<FullTask>& ft){
    Date date = ft.lock()->getTask().getDate();
    Task::Priority priority = ft.lock()->getTask().getPrior();
    map_[date].deleteTask(priority, ft.lock()->getId());

}