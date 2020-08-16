//
// Created by illia.dmitriiev on 8/11/2020.
//

#ifndef TODOLIST_TASKSERVICECREATOR_H
#define TODOLIST_TASKSERVICECREATOR_H

#include "TaskService.h"

/*
 *  TaskService injector
 *
 *  @author: Ilya Dmitriev
 */

namespace todo_list{
    /*
     * Generates TaskService
     *
     * @return instance of  TaskService.
     */
    TaskService createService() {
        auto generator = std::make_unique<IDGenerator>();
        auto viewByPriority = std::make_unique<ViewByPriority>();
        auto viewByDate = std::make_unique<ViewByDate>();
        auto storage = std::make_unique<TaskStorage>();
        return TaskService(std::move(generator), std::move(viewByPriority), std::move(viewByDate), std::move(storage));
    }

}

#endif //TODOLIST_TASKSERVICECREATOR_H
