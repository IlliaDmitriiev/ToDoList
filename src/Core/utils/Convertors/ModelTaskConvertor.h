//
// Created by ilya on 30.09.2020.
//

#ifndef TODOLIST_MODELTASKCONVERTOR_H
#define TODOLIST_MODELTASKCONVERTOR_H

#include "Core/model/api/ModelTaskDTO.h"
#include "Core/model/FullTask.h"

class ModelTaskConvertor {
public:
    static Task transferToTask(ModelTaskDTO);
    static FullTask transferToFullTask(ModelTaskDTO);
    static ModelTaskDTO transferToModelTaskDTO(const FullTask&);
};

#endif //TODOLIST_MODELTASKCONVERTOR_H
