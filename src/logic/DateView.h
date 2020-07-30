//
// Created by Илля on 30.07.2020.
//

#ifndef TODOLIST_DATEVIEW_H
#define TODOLIST_DATEVIEW_H

#include "StorageByDate.h"

#include <iostream>

class DateView {
public:
    std::vector<std::weak_ptr<FullTask>> getTasksForToday(StorageByDate data);
    std::vector<std::weak_ptr<FullTask>> getTasksForWeek(StorageByDate data);

};


#endif //TODOLIST_DATEVIEW_H
