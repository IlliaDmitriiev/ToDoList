//
// Created by hp on 06.09.2020.
//

#ifndef TESTCLI_CONSOLEIO_H
#define TESTCLI_CONSOLEIO_H

#include "IO.h"

class ConsoleIO: public IO{

public:
    std::string input() override;
    void output(std::string) override;

};


#endif //TESTCLI_CONSOLEIO_H
