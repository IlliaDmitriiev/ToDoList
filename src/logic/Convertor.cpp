//
// Created by Илля on 02.08.2020.
//

#include "Convertor.h"

TaskDTO Convertor::convert(FullTask ft){
    return TaskDTO::create(
            ft.getId(),
            ft.getTask().getDate(),
            ft.getTask().getName(),
            ft.getTask().getLabel(),
            ft.getTask().getPrior()
            );
}
