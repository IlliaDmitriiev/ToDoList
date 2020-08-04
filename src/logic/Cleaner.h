//
// Created by Илля on 03.08.2020.
//

#ifndef TODOLIST_CLEANER_H
#define TODOLIST_CLEANER_H

#include "StorageForSharedPtr.h"
#include "StorageByPrior.h"
#include "StorageByDate.h"

class Cleaner {

public:
    void deleteTask(StorageForSharedPtr& storage, TaskID id);
    void deleteDanglingPointers(StorageByPrior& storage);
    void deleteDanglingPointers(StorageByDate& storage);
};


#endif //TODOLIST_CLEANER_H