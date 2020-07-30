//
// Created by Илля on 30.07.2020.
//

#include "DateView.h"


std::vector<std::weak_ptr<FullTask>> DateView::getTasksForToday(StorageByDate data){
    time_t now = time(0);
    auto cur = std::make_unique<tm>(*gmtime(&now));
    Date date = Date::create(cur->tm_year+1900, cur->tm_mon + 1, cur->tm_mday);

    std::cout<<date.getYear()<<" "<<date.getMounth()<<" "<<date.getDay()<<" -> today\n";
    auto mp = data.getMp();
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

std::vector<std::weak_ptr<FullTask>>  DateView::getTasksForWeek(StorageByDate data){
    time_t now = time(0);
    auto cur = std::make_unique<tm>(*gmtime(&now));

    Date date = Date::create(cur->tm_year+1900, cur->tm_mon + 1, cur->tm_mday);
    auto mp = data.getMp();
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
