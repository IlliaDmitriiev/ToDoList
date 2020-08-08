//
// Created by Илля on 02.08.2020.
//

#ifndef TODOLIST_CONVERTOR_H
#define TODOLIST_CONVERTOR_H

#include "FullTask.h"
#include "api/TaskDTO.h"

class Convertor{

public:
    static TaskDTO getTaskDTO(std::weak_ptr<FullTask> ft);
    static Task getTask(TaskDTO td);

};


#endif //TODOLIST_CONVERTOR_H
