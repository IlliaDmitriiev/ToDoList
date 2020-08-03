//
// Created by Илля on 03.08.2020.
//

#include "Collector.h"


void Collector::deleteTask(StorageForSharedPtr& storage, TaskID id){
    storage.deleteTask(id);
}

void Collector::deleteDanglingPointers(StorageByPrior& storage){
    storage.deleteDanglingPointers();
}

void Collector::deleteDanglingPointers(StorageByDate& storage){
    storage.deleteDanglingPointers();
}