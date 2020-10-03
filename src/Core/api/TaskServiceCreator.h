//
// Created by illia.dmitriiev on 8/11/2020.
//

#ifndef TODOLIST_TASKSERVICECREATOR_H
#define TODOLIST_TASKSERVICECREATOR_H

#include "TaskService.h"
#include "Core/model/DataHolderCreator.h"

/*
 *  TaskService injector
 *
 *  @author: Ilya Dmitriev
 */

namespace todo_list_Core{
    /*
     * Generates TaskService
     *
     * @return instance of  TaskService.
     */
    static std::unique_ptr<TaskService> createService() {

        auto model = todo_list_model::createDataHolder();

        return std::make_unique<TaskService>(std::move(model));
    }

}

#endif //TODOLIST_TASKSERVICECREATOR_H
