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

void Cleaner::increaseTotalCount(int x){
    totalTaskCount += x;
}

void Cleaner::increaseDeletedCount(int x){
    deletedTaskCount += x;
}

bool Cleaner::isItTimeToUpdate(){
    if(deletedTaskCount * 5 >= totalTaskCount){
        totalTaskCount -= deletedTaskCount;
        deletedTaskCount = 0;
        return true;
    }
    else return false;
}

