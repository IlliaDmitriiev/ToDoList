//
// Created by Илля on 30.07.2020.
//

#include "ViewByDate.h"


std::vector<std::weak_ptr<FullTask>> ViewByDate::getTasksForToday(Date date){

    auto mp = storage_.getMap();
    auto NeedData = mp.find(date);

    std::vector<std::weak_ptr<FullTask>> v;
    if(NeedData!=mp.end()){
        auto vFirst = NeedData->second.getVFirstPrior();
        auto vSecond = NeedData->second.getVSecondPrior();
        auto vThird = NeedData->second.getVThirdPrior();
        auto vNone = NeedData->second.getVNonePrior();
        for (auto i: vFirst)
            if (!i.expired())
                v.push_back(i);
        for (auto i: vSecond)
            if (!i.expired())
                v.push_back(i);
        for (auto i: vThird)
            if (!i.expired())
                v.push_back(i);
        for (auto i: vNone)
            if (!i.expired())
                v.push_back(i);
    }
    return v;
}

std::vector<std::weak_ptr<FullTask>>  ViewByDate::getTasksForWeek(Date date){

    auto mp = storage_.getMap();
    std::vector<std::weak_ptr<FullTask>> v;

    for (int i = 1; i<=7; ++i) {
        int WeekDay = date.getWday();
        if (WeekDay == 0) WeekDay = 7;
        date.moveWithinTheWeek(i - WeekDay);

        auto NeedData = mp.find(date);
        if (NeedData != mp.end()) {
            auto vFirst = NeedData->second.getVFirstPrior();
            auto vSecond = NeedData->second.getVSecondPrior();
            auto vThird = NeedData->second.getVThirdPrior();
            auto vNone = NeedData->second.getVNonePrior();
            for (auto i: vFirst)
                if (!i.expired())
                    v.push_back(i);
            for (auto i: vSecond)
                if (!i.expired())
                    v.push_back(i);
            for (auto i: vThird)
                if (!i.expired())
                    v.push_back(i);
            for (auto i: vNone)
                if (!i.expired())
                    v.push_back(i);
        }
    }
    return v;
}

StorageByDate &ViewByDate::getStorage() {
    return storage_;
}
