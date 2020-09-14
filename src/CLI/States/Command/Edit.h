//
// Created by hp on 13.09.2020.
//

#ifndef TODOLIST_EDIT_H
#define TODOLIST_EDIT_H

#include "CommandState.h"

class Edit: public CommandState{
public:
    CommandState::Type read(IO&) override;
    void print(IO&) override;
    std::unique_ptr<CommandState> change(CommandState::Type) override;
};


#endif //TODOLIST_EDIT_H
