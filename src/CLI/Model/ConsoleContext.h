//
// Created by hp on 06.09.2020.
//

#ifndef TESTCLI_CONTEXT_H
#define TESTCLI_CONTEXT_H

#include "Context.h"

class ConsoleContext: public Context{

public:
    static ConsoleContext create(std::unique_ptr<Proxy> proxy){
        return ConsoleContext(std::move(proxy));
    }

public:
    Proxy& getService()override{return *proxy_server_;}
    std::vector<TaskDTO>& getTaskList()override{return task_list_;}

private:
    explicit ConsoleContext(std::unique_ptr<Proxy> proxy)
    :
    proxy_server_(std::move(proxy)){ }

private:
    std::unique_ptr<Proxy> proxy_server_;
    std::vector<TaskDTO> task_list_;
};

#endif //TESTCLI_CONTEXT_H
