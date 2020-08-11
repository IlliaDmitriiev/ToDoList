//
// Created by Илля on 02.08.2020.
//

#include "TaskConvertor.h"

TaskDTO TaskConvertor::transferToTaskDTO(std::weak_ptr<FullTask> ft){
    return TaskDTO::create(
            ft.lock()->getId(),
            ft.lock()->getTask().getDate(),
            ft.lock()->getTask().getName(),
            ft.lock()->getTask().getLabel(),
            ft.lock()->getTask().getPrior()
            );
}

Task TaskConvertor::transferToTask(TaskDTO td){
    return Task::create(
            td.getDate(),
            td.getName(),
            td.getLabel(),
            td.getPrior()
            );
}
