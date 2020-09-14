//
// Created by hp on 06.09.2020.
//

#ifndef TESTCLI_IO_H
#define TESTCLI_IO_H

#include <string>

/*
 *  Object which has ability
 *  to input and output info.
 *
 *  @author: Ilya Dmitriev
 */

class IO{

public:
    virtual std::string input() = 0;
    virtual void output(std::string) = 0;

};

#endif //TESTCLI_IO_H
