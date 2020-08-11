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

void View::addTask(const std::weak_ptr<FullTask>& ft){
    viewByD_.addTask(ft);
    viewByP_.addTask(ft);
}

void View::deleteTask(const std::weak_ptr<FullTask>& ft){
    viewByD_.deleteTask(ft);
    viewByP_.deleteTask(ft.lock()->getTask().getPrior(), ft.lock()->getId());
}
