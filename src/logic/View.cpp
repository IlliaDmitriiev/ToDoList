//
// Created by Илля on 01.08.2020.
//

#include "View.h"

std::vector<std::weak_ptr<FullTask>> View::getAllTasksByPrior(){
    return viewByP_.getAllTasks();
}

std::vector<std::weak_ptr<FullTask>> View::getTasksForToday(){


    return viewByD_.getTasksForToday();
}

std::vector<std::weak_ptr<FullTask>> View::getTasksForWeek(){


    return viewByD_.getTasksForWeek();
}

ViewByDate &View::getViewByD() {
    return viewByD_;
}

ViewByPriority &View::getViewByP()  {
    return viewByP_;
}


