//
// Created by Илля on 02.08.2020.
//

#ifndef TODOLIST_TASKCONVERTOR_H
#define TODOLIST_TASKCONVERTOR_H

#include "FullTask.h"
#include "api/TaskDTO.h"

class TaskConvertor{

public:
    static TaskDTO transferToTaskDTO(std::weak_ptr<FullTask> ft);
    static Task transferToTask(TaskDTO td);

};


#endif //TODOLIST_TASKCONVERTOR_H
