//
// Created by hp on 14.09.2020.
//

#ifndef TODOLIST_VIEW_H
#define TODOLIST_VIEW_H

#include "CommandState.h"

class View: public CommandState{
public:
    CommandState::Type read(IO&) override;
    void print(IO&) override;
    std::unique_ptr<CommandState> change(CommandState::Type) override;
};


#endif //TODOLIST_VIEW_H
