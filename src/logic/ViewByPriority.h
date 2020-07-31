//
// Created by Илля on 31.07.2020.
//

#ifndef TODOLIST_PRIORITYVIEW_H
#define TODOLIST_PRIORITYVIEW_H

#include "StorageByPrior.h"

class ViewByPriority {

public:
    StorageByPrior &getStorage();

    std::vector<std::weak_ptr<FullTask>> getAllTasks();

private:
    StorageByPrior storage_;
};


#endif //TODOLIST_PRIORITYVIEW_H
