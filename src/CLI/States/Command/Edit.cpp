//
// Created by hp on 13.09.2020.
//

#include "Edit.h"
#include "Option.h"
#include "Validate.h"

CommandState::Type Edit::read(IO& io){
    return validate::make(io.input());
}

void Edit::print(IO& io){
    io.output("Available commands:\nedit\nback\nExample of input: edit\n");
}

std::unique_ptr<CommandState> Edit::change(CommandState::Type){
    return std::make_unique<Option>();
}