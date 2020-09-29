//
// Created by hp on 06.09.2020.
//

#ifndef TESTCLI_CONTEXT_H
#define TESTCLI_CONTEXT_H

#include "Context.h"

class ConsoleContext: public Context{

public:
    static ConsoleContext create(std::unique_ptr<TaskServiceInterface> ts){
        return ConsoleContext(std::move(ts));
    }

public:
    TaskServiceInterface& getService()override{return *ts_;}
    std::vector<ServiceTaskDTO>& getTaskList()override{return task_list_;}

private:
    explicit ConsoleContext(std::unique_ptr<TaskServiceInterface> ts):ts_(std::move(ts)){ }

private:
    std::unique_ptr<TaskServiceInterface> ts_;
    std::vector<ServiceTaskDTO> task_list_;
};

#endif //TESTCLI_CONTEXT_H
