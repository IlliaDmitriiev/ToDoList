//
// Created by ilya on 04.10.2020.
//

#ifndef TODOLIST_PROTOTASKCONVERTOR_H
#define TODOLIST_PROTOTASKCONVERTOR_H

#include "Model.pb.h"
#include "Core/model/ModelTaskDTO.h"

/*
 *  Class-convertor
 *
 *  @author: Ilya Dmitriev
 */
class ProtoTaskConvertor {
public:
    static ModelTaskDTO transferToModelTask(const TaskStructure&);
    static TaskStructure transferToTaskStructure(const ModelTaskDTO&);
};


#endif //TODOLIST_PROTOTASKCONVERTOR_H
