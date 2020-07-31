//
// Created by Илля on 30.07.2020.
//

#ifndef TODOLIST_VIEWBYPRIORITY_H
#define TODOLIST_VIEWBYPRIORITY_H

#include "StorageByDate.h"

#include <iostream>

class ViewByDate {
public:
    std::vector<std::weak_ptr<FullTask>> getTasksForToday(const StorageByDate& data);
    std::vector<std::weak_ptr<FullTask>> getTasksForWeek(const StorageByDate& data);

    StorageByDate &getData();

private:
    StorageByDate data;
};


#endif //TODOLIST_VIEWBYPRIORITY_H
