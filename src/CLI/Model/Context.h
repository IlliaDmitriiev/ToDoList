//
// Created by hp on 10.09.2020.
//

#ifndef TODOLIST_CONTEXT_H
#define TODOLIST_CONTEXT_H

#include <string>
#include <vector>
#include "CLI/Proxy/Proxy.h"

/*
 *  Storage of current tasks and taskService.
 *
 *  @author: Ilya Dmitriev
 */

class Context{

public:
    /*
     * Gives access to the service.
     *
     * @return instance of TaskService.
     */
    virtual Proxy& getService() = 0;
    /*
     * Gives current list of tasks according to the last request.
     *
     * @return list of ServiceTaskDTO objects.
     */
    virtual std::vector<TaskDTO>& getTaskList() = 0;

    virtual ~Context() = default;

};

#endif //TODOLIST_CONTEXT_H
