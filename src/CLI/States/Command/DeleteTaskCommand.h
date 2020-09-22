//
// Created by hp on 15.09.2020.
//

#ifndef TODOLIST_DELETETASKCOMMAND_H
#define TODOLIST_DELETETASKCOMMAND_H

#include "CommandState.h"

class DeleteTaskCommand: public CommandState {

public:
    CommandState::Type read(IO&) override;
    void print(IO&) override;
    void execute(IO&, Context&) override;
    std::unique_ptr<CommandState> change(CommandState::Type) override;

};


#endif //TODOLIST_DELETETASKCOMMAND_H
