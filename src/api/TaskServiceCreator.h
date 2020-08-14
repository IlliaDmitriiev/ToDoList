//
// Created by illia.dmitriiev on 8/11/2020.
//

#ifndef TODOLIST_TASKSERVICECREATOR_H
#define TODOLIST_TASKSERVICECREATOR_H

#include "TaskService.h"

namespace todo_list{

    TaskService createService() {
        auto viewByPriority = std::make_unique<ViewByPriority>();
        auto viewByDate = std::make_unique<ViewByDate>();
        auto storage = std::make_unique<TaskStorage>();
        return TaskService(std::move(viewByPriority), std::move(viewByDate), std::move(storage));
    }

}

#endif //TODOLIST_TASKSERVICECREATOR_H
