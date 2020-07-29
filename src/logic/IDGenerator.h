//
// Created by illia.dmitriiev on 7/27/2020.
//

#ifndef TODOLIST_IDGENERATOR_H
#define TODOLIST_IDGENERATOR_H

#include "TaskID.h"

class IDGenerator {

public:
    TaskID generateId();

    IDGenerator(int id=0);
private:
    int id;
};


#endif //TESTP_IDGENERATOR_H
