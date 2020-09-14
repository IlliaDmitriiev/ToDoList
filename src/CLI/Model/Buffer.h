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

struct Buffer{

    struct Parametrs{
        std::string name_;
        std::string label_;
        boost::gregorian::date date_;
        int id_;
        TaskPriority priority_;
    };

    Parametrs buf_;
};

#endif //TESTCLI_BUFFER_H
