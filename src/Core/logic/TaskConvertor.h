//
// Created by Илля on 02.08.2020.
//

#ifndef TODOLIST_TASKCONVERTOR_H
#define TODOLIST_TASKCONVERTOR_H

#include "Core/model/FullTask.h"
#include "Core/api/ServiceTaskDTO.h"
/*
 *  Class-convertor
 *
 *  @author: Ilya Dmitriev
 */
class TaskConvertor{

public:
    static ServiceTaskDTO transferToTaskDTO(std::weak_ptr<FullTask> ft);
    static Task transferToTask(ServiceTaskDTO td);

};


#endif //TODOLIST_TASKCONVERTOR_H
