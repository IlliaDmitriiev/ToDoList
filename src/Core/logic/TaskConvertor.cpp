//
// Created by Илля on 02.08.2020.
//

#include "TaskConvertor.h"

ServiceTaskDTO TaskConvertor::transferToTaskDTO(std::weak_ptr<FullTask> ft){
    return ServiceTaskDTO::create(
            ft.lock()->getId(),
            ft.lock()->getTask().getDate(),
            ft.lock()->getTask().getName(),
            ft.lock()->getTask().getLabel(),
            ft.lock()->getTask().getPriority()
            );
}

Task TaskConvertor::transferToTask(ServiceTaskDTO td){
    return Task::create(
            td.getDate(),
            td.getName(),
            td.getLabel(),
            td.getPriority()
            );
}
