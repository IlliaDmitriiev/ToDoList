//
// Created by Илля on 02.08.2020.
//

#include "TaskConvertor.h"

ModelTaskDTO TaskConvertor::transferToModelDTO(ServiceTaskDTO task){
    return ModelTaskDTO::create(task.getId(),
                                task.getDate(),
                                task.getName(),
                                task.getLabel(),
                                task.getPriority(),
                                task.isCompleted()
    );
}

ServiceTaskDTO TaskConvertor::transferToServiceDTO(ModelTaskDTO task){
    return ServiceTaskDTO::create(task.getId(),
                                  task.getDate(),
                                  task.getName(),
                                  task.getLabel(),
                                  task.getPriority(),
                                  task.isCompleted()
    );
}

