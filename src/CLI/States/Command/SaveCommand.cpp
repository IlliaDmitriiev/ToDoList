//
// Created by ilya on 11.10.2020.
//

#include "SaveCommand.h"
#include "CLI/Namespaces/CommandMapCreator.h"

CommandState::Type SaveCommand::read(IO&) {
    return CommandState::Type::Option;
}

void SaveCommand::print(IO&) {

}

void SaveCommand::execute(IO& io, Context& context) {

    auto &service = context.getService();
    auto result = service.save();
    if ( ResultType::FAILURE == result.result) {
        io.output(result.error_message);
    }
    else {
        io.output("System was saved successfully.");
    }

}

std::unique_ptr<CommandState> SaveCommand::change(CommandState::Type type) {
    auto command_map = CommandMap::create();
    return std::move(command_map[type]);
}
