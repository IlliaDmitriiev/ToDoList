//
// Created by ilya on 30.09.2020.
//

#ifndef TODOLIST_DATAHOLDERCREATOR_H
#define TODOLIST_DATAHOLDERCREATOR_H

#include "Core/model/DataHolder.h"
#include "Core/logic/ViewByDate.h"
#include "Core/logic/ViewByPriority.h"
#include "Core/model/TaskStorage.h"

/*
 *  Model injector
 *
 *  @author: Ilya Dmitriev
 */

namespace todo_list_model{
    /*
     * Generates Model api
     *
     * @return instance of DataHolder.
     */
    static std::unique_ptr<DataHolder> createDataHolder() {
        auto generator = std::make_unique<IDGenerator>();
        auto byPriority = std::make_unique<ViewByPriority>();
        auto byDate = std::make_unique<ViewByDate>();
        auto storage = std::make_unique<TaskStorage>();

        return std::make_unique<DataHolder>(std::move(generator),
                                            std::move(byPriority),
                                            std::move(byDate),
                                            std::move(storage));
    }

}

#endif //TODOLIST_DATAHOLDERCREATOR_H
