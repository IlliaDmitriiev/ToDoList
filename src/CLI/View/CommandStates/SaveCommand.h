//
// Created by ilya on 11.10.2020.
//

#ifndef TODOLIST_SAVECOMMAND_H
#define TODOLIST_SAVECOMMAND_H

#include "CommandState.h"

class SaveCommand: public CommandState {

public:
    CommandState::Type read(IO&) override;
    void print(IO&) override;
    void execute(IO&, Context&) override;
    std::unique_ptr<CommandState> change(CommandState::Type) override;

};

#endif //TODOLIST_SAVECOMMAND_H
