//
// Created by ilya on 31.10.2020.
//

#ifndef TODOLIST_TASKID_H
#define TODOLIST_TASKID_H

#include<iostream>
/*
 *  Class-wrapper of ID to hide its implementation
 *
 *  @author: Ilya Dmitriev
 */
class TaskID {

public:
    static TaskID create(int id){return TaskID(id);}

public:
    unsigned int ID() const{return id_;}

private:
    TaskID(unsigned int id){id_ = id;}

private:
    unsigned int id_;
};

#endif //TODOLIST_TASKID_H
