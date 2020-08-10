//
// Created by Илля on 31.07.2020.
//

#ifndef TODOLIST_PRIORITYVIEW_H
#define TODOLIST_PRIORITYVIEW_H

#include "StorageByPriority.h"

class ViewByPriority {

public:
    StorageByPriority &getStorage();
    std::vector<std::weak_ptr<FullTask>> getAllTasks();

private:
    StorageByPriority storage_;
};


#endif //TODOLIST_PRIORITYVIEW_H
