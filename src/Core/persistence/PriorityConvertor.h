//
// Created by ilya on 04.10.2020.
//

#ifndef TODOLIST_PRIORITYCONVERTOR_H
#define TODOLIST_PRIORITYCONVERTOR_H

#include "Model.pb.h"
#include "Core/api/TaskPriority.h"

/*
 *  Class-convertor
 *
 *  @author: Ilya Dmitriev
 */
class PriorityConvertor {
public:
    static TaskPriority tranferToPriority(TaskStructure::Priority);
    static TaskStructure::Priority tranferToProtoPriority(TaskPriority);

};


#endif //TODOLIST_PRIORITYCONVERTOR_H
