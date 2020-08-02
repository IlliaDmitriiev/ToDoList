//
// Created by Илля on 02.08.2020.
//

#ifndef TODOLIST_CONVERTOR_H
#define TODOLIST_CONVERTOR_H

#include "FullTask.h"
#include "TaskDTO.h"

class Convertor{

public:
    TaskDTO convert(FullTask ft);
};


#endif //TODOLIST_CONVERTOR_H
