//
// Created by hp on 13.09.2020.
//

#ifndef TODOLIST_EDITTASKCOMMAND_H
#define TODOLIST_EDITTASKCOMMAND_H

#include "CommandState.h"

class EditTaskCommand: public CommandState{

public:
    CommandState::Type read(IO&) override;
    void print(IO&) override;
    void execute(IO&, Context&) override;
    std::unique_ptr<CommandState> change(CommandState::Type) override;

};


#endif //TODOLIST_EDITTASKCOMMAND_H
