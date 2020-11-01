//
// Created by ilya on 04.10.2020.
//

#ifndef TODOLIST_PERSISTER_H
#define TODOLIST_PERSISTER_H

#include "Core/model/api/DataInterface.h"
/*
 *  Persistence
 *
 *  @author: Ilya Dmitriev
 */
class Persister{

public:
    /*
     * saves all tasks
     *
     * @return true, if operation is successful, false otherwise.
     */
    virtual bool save() = 0;
    /*
     * loads all tasks in system
     *
     * @return true, if operation is successful, false otherwise.
     */
    virtual bool load() = 0;
    virtual ~Persister() = default;
};

#endif //TODOLIST_PERSISTER_H
