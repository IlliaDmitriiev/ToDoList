//
// Created by illia.dmitriiev on 8/11/2020.
//

#ifndef TODOLIST_CREATOR_H
#define TODOLIST_CREATOR_H

#include "TaskService.h"

namespace Creator {

    TaskService createService() {
        auto viewByPriority = std::make_unique<ViewByPriority>();
        auto viewByDate = std::make_unique<ViewByDate>();
        return TaskService(std::move(viewByPriority), std::move(viewByDate));
    }
}
#endif //TODOLIST_CREATOR_H
