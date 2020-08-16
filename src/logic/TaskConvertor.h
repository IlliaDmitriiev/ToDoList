//
// Created by Илля on 02.08.2020.
//

#ifndef TODOLIST_TASKCONVERTOR_H
#define TODOLIST_TASKCONVERTOR_H

#include "model/FullTask.h"
#include "api/TaskDTO.h"
/*
 *  Class-convertor
 *
 *  @author: Ilya Dmitriev
 */
class TaskConvertor{

public:
    static TaskDTO transferToTaskDTO(std::weak_ptr<FullTask> ft);
    static Task transferToTask(TaskDTO td);

};


#endif //TODOLIST_TASKCONVERTOR_H
