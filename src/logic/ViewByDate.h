//
// Created by Илля on 30.07.2020.
//

#ifndef TODOLIST_VIEWBYPRIORITY_H
#define TODOLIST_VIEWBYPRIORITY_H

#include "StorageByDate.h"

#include <iostream>

class ViewByDate {
public:
    std::vector<std::weak_ptr<FullTask>> getTasksForToday();
    std::vector<std::weak_ptr<FullTask>> getTasksForWeek();

    StorageByDate &getStorage();

private:
    StorageByDate storage_;
};


#endif //TODOLIST_VIEWBYPRIORITY_H
