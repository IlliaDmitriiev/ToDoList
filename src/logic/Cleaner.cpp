//
// Created by Илля on 03.08.2020.
//

#include "Cleaner.h"

Cleaner::Cleaner() :totalTaskCount_(0), deletedTaskCount_(0){}

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
    totalTaskCount_ += x;
}

void Cleaner::increaseDeletedCount(int x){
    deletedTaskCount_ += x;
}

bool Cleaner::isItTimeToUpdate(){
    if(deletedTaskCount_ * 5 >= totalTaskCount_){
        totalTaskCount_ -= deletedTaskCount_;
        deletedTaskCount_ = 0;
        return true;
    }
    else return false;
}

