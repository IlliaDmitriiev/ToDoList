//
// Created by ilya on 30.09.2020.
//

#include "ModelTaskConvertor.h"

Task ModelTaskConvertor::transferToTask(ModelTaskDTO taskDTO){
    return Task::create(taskDTO.getDate(),
                        taskDTO.getName(),
                        taskDTO.getLabel(),
                        taskDTO.getPriority()
    );
}

FullTask ModelTaskConvertor::transferToFullTask(ModelTaskDTO taskDTO){
    return FullTask::create( taskDTO.getId(),
                             Task::create(taskDTO.getDate(),
                                          taskDTO.getName(),
                                          taskDTO.getLabel(),
                                          taskDTO.getPriority()));
}

ModelTaskDTO ModelTaskConvertor::transferToModelTaskDTO(const FullTask& task){
    return ModelTaskDTO::create(task.getId(),
                                task.getTask().getDate(),
                                task.getTask().getName(),
                                task.getTask().getLabel(),
                                task.getTask().getPriority(),
                                task.isComplete()
    );
}
