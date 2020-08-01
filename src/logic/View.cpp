//
// Created by Илля on 01.08.2020.
//

#include "View.h"

std::vector<std::weak_ptr<FullTask>> View::getAllTasksByPrior(){
    return viewByP_.getAllTasks();
}

std::vector<std::weak_ptr<FullTask>> View::getTasksForToday(){
    time_t now = time(0);
    auto cur = std::make_unique<tm>(*gmtime(&now));
    Date date = Date::create(cur->tm_year+1900, cur->tm_mon + 1, cur->tm_mday);

    return viewByD_.getTasksForToday(date);
}

std::vector<std::weak_ptr<FullTask>> View::getTasksForWeek(){
    time_t now = time(0);
    auto cur = std::make_unique<tm>(*gmtime(&now));
    Date date = Date::create(cur->tm_year+1900, cur->tm_mon + 1, cur->tm_mday);

    return viewByD_.getTasksForWeek(date);
}

ViewByDate &View::getViewByD() {
    return viewByD_;
}

ViewByPriority &View::getViewByP()  {
    return viewByP_;
}


