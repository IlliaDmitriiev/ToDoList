//
// Created by Илля on 03.08.2020.
//

#include "Cleaner.h"


void Cleaner::deleteTask(StorageForSharedPtr& storage, TaskID id){
    storage.deleteTask(id);
}

void Cleaner::deleteDanglingPointers(StorageByPrior& storage){
    storage.deleteDanglingPointers();
}

void Cleaner::deleteDanglingPointers(StorageByDate& storage){
    storage.deleteDanglingPointers();
}