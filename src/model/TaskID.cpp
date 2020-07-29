//
// Created by illia.dmitriiev on 7/27/2020.
//

#include "TaskID.h"

TaskID TaskID::create(int id){
    TaskID taskId(id);
    return taskId;
}

int TaskID::getId() const {
    return id;
}

TaskID::TaskID(int id) : id(id) {}
