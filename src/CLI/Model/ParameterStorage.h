//
// Created by hp on 08.09.2020.
//

#ifndef TESTCLI_BUFFER_H
#define TESTCLI_BUFFER_H

#include <string>
#include "Core/api/TaskPriority.h"
#include "boost/date_time/gregorian/gregorian.hpp"


/*
 *  Storage of input parameters.
 *
 *  @author: Ilya Dmitriev
 */
class ParameterStorage{

public:
    struct Parameters{
        std::string name_;
        std::string label_;
        boost::gregorian::date date_;
        int id_;
        TaskPriority priority_;
    };

public:
    static ParameterStorage create(){
        return ParameterStorage();
    }

    Parameters &getParameters(){return parameters_;}

private:
    ParameterStorage() = default;

private:
    Parameters parameters_;
};

#endif //TESTCLI_BUFFER_H
