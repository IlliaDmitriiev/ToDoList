//
// Created by hp on 17.09.2020.
//

#ifndef TODOLIST_SUBMENUCOMMAND_H
#define TODOLIST_SUBMENUCOMMAND_H

#include "CommandState.h"

class SubmenuCommand: public CommandState{
public:
    CommandState::Type read(IO&) override;
    void print(IO&) override;
    void execute(IO&, Context&) override;
    std::unique_ptr<CommandState> change(CommandState::Type) override;
};



#endif //TODOLIST_SUBMENUCOMMAND_H
