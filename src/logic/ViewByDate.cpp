//
// Created by Илля on 30.07.2020.
//

#include "ViewByDate.h"


std::vector<std::weak_ptr<FullTask>> ViewByDate::getTasksForToday(Date date){

    auto DataMap = storage_.getMap();
    auto Node = DataMap.find(date);
    std::vector<std::weak_ptr<FullTask>> v;

    if(Node!=DataMap.end()){
        auto PriorityMap = Node->second.getMap();

        for( auto i: PriorityMap[1])
            v.push_back(i.second);
        for( auto i: PriorityMap[2])
            v.push_back(i.second);
        for( auto i: PriorityMap[3])
            v.push_back(i.second);
        for( auto i: PriorityMap[0])
            v.push_back(i.second);
    }
    return v;
}

std::vector<std::weak_ptr<FullTask>>  ViewByDate::getTasksForWeek(Date date){

    auto map = storage_.getMap();
    std::vector<std::weak_ptr<FullTask>> v;

    for (int i = 1; i<=7; ++i) {
        int WeekDay = date.getWday();
        if (WeekDay == 0) WeekDay = 7;
        date.moveWithinTheWeek(i - WeekDay);

        auto NeedData = map.find(date);
        if (NeedData != map.end()) {
            auto PriorityMap = NeedData->second.getMap();

            for( auto i: PriorityMap[1])
                v.push_back(i.second);
            for( auto i: PriorityMap[2])
                v.push_back(i.second);
            for( auto i: PriorityMap[3])
                v.push_back(i.second);
            for( auto i: PriorityMap[0])
                v.push_back(i.second);
        }
    }
    return v;
}

StorageByDate &ViewByDate::getStorage() {
    return storage_;
}
