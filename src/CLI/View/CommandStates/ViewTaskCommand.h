//
// Created by hp on 14.09.2020.
//

#ifndef TODOLIST_VIEWTASKCOMMAND_H
#define TODOLIST_VIEWTASKCOMMAND_H

#include "CommandState.h"

class ViewTaskCommand: public CommandState{
public:
    CommandState::Type read(IO&) override;
    void print(IO&) override;
    void execute(IO&, Context&) override;
    std::unique_ptr<CommandState> change(CommandState::Type) override;
};


#endif //TODOLIST_VIEWTASKCOMMAND_H
