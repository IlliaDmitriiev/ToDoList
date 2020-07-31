//
// Created by Илля on 31.07.2020.
//

#ifndef TODOLIST_PRIORITYVIEW_H
#define TODOLIST_PRIORITYVIEW_H

#include "StorageByPrior.h"

class ViewByPriority {

public:
    StorageByPrior &getSbp();

    std::vector<std::weak_ptr<FullTask>> getAllTasks(const StorageByPrior& sbp);

private:
    StorageByPrior sbp;
};


#endif //TODOLIST_PRIORITYVIEW_H
