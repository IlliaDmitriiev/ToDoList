//
// Created by illia.dmitriiev on 8/11/2020.
//

#ifndef TODOLIST_INJECTOR_H
#define TODOLIST_INJECTOR_H

#include "TaskService.h"

namespace Injector {

    TaskService createService() {
        auto viewByPriority = std::make_unique<ViewByPriority>();
        auto viewByDate = std::make_unique<ViewByDate>();
        return TaskService(std::move(viewByPriority), std::move(viewByDate));
    }
}
#endif //TODOLIST_INJECTOR_H
