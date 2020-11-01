//
// Created by ilya on 31.10.2020.
//

#ifndef TODOLIST_PROTOCONVERTOR_H
#define TODOLIST_PROTOCONVERTOR_H

#include "Model.pb.h"
#include "TaskService.pb.h"
#include "CLI/Proxy/Data/TaskDTO.h"
#include "CLI/Proxy/Data/ReturnType.h"

/*
 *  Class-convertor
 *
 *  @author: Ilya Dmitriev
 */
class ProtoConvertor {

public:
    static TaskPriority tranferToPriority(TaskStructure::Priority);
    static TaskStructure::Priority tranferToProtoPriority(TaskPriority);

public:
    static TaskDTO transferToTaskDTO(const TaskStructure&);
    static TaskStructure transferToProtoTask(const TaskDTO&);

public:
    static AddTaskResult    transferToReturnType(const AddTaskResponse&);
    static RequstTaskResult transferToReturnType(const RequstTaskResponse&);

};


#endif //TODOLIST_PROTOCONVERTOR_H
