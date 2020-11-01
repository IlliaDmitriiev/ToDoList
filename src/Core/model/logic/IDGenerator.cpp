//
// Created by illia.dmitriiev on 7/27/2020.
//

#include "IDGenerator.h"

TaskID IDGenerator::generateId() {
    return TaskID::create((this->id_)++);
}

IDGenerator::IDGenerator() : id_(0){}