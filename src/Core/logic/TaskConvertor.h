//
// Created by Илля on 02.08.2020.
//

#ifndef TODOLIST_TASKCONVERTOR_H
#define TODOLIST_TASKCONVERTOR_H

#include "Core/model/ModelTaskDTO.h"
#include "Core/api/ServiceTaskDTO.h"
/*
 *  Class-convertor
 *
 *  @author: Ilya Dmitriev
 */
class TaskConvertor{

public:
    static ModelTaskDTO transferToModelDTO(ServiceTaskDTO);
    static ServiceTaskDTO transferToServiceDTO(ModelTaskDTO);

};


#endif //TODOLIST_TASKCONVERTOR_H
