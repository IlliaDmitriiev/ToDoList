//
// Created by hp on 07.09.2020.
//

#ifndef TESTCLI_OPTION_H
#define TESTCLI_OPTION_H

#include "CommandState.h"
#include <iostream>

class CommandOption: public CommandState {

public:
    CommandState::Type read(IO&) override;
    void print(IO&) override;
    void execute(IO&, Context&) override;
    std::unique_ptr<CommandState> change(CommandState::Type) override;

};

#endif //TESTCLI_OPTION_H
