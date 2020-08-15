//
// Created by Илля on 15.08.2020.
//

#ifndef TODOLIST_IDGENERATORINTERFACE_H
#define TODOLIST_IDGENERATORINTERFACE_H

#include "api/TaskID.h"

class IDGeneratorInterface{
public:
    virtual TaskID generateId() = 0;
    virtual ~IDGeneratorInterface() = default;
};

#endif //TODOLIST_IDGENERATORINTERFACE_H
