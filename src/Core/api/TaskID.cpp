//
// Created by illia.dmitriiev on 7/27/2020.
//

#include "TaskID.h"

TaskID TaskID::create(int id){
    if (id<0)
        throw std::runtime_error("negative id");
    TaskID taskId(id);
    return taskId;
}

unsigned int TaskID::getId() const {
    return id_;
}

TaskID::TaskID(unsigned int id) : id_(id) {}
