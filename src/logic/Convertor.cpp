//
// Created by Илля on 02.08.2020.
//

#include "Convertor.h"

TaskDTO Convertor::convert(std::weak_ptr<FullTask> ft){
    return TaskDTO::create(
            ft.lock()->getId(),
            ft.lock()->getTask().getDate(),
            ft.lock()->getTask().getName(),
            ft.lock()->getTask().getLabel(),
            ft.lock()->getTask().getPrior()
            );
}
