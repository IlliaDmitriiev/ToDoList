//
// Created by illia.dmitriiev on 7/27/2020.
//

#ifndef TODOLIST_IDGENERATOR_H
#define TODOLIST_IDGENERATOR_H

#include "api/TaskID.h"

class IDGenerator {

public:
    TaskID generateId();

    IDGenerator();
private:
    unsigned int id_;
};


#endif //TESTP_IDGENERATOR_H
