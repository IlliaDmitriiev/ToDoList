//
// Created by ilya on 11.10.2020.
//

#include "SaveCommand.h"
#include "CLI/Utils/Creators/GraphCreator.h"
#include "CLI/Utils/Creators/CommandMapCreator.h"

CommandState::Type SaveCommand::read(IO&) {
    return CommandState::Type::Option;
}

void SaveCommand::print(IO&) {

}

void SaveCommand::execute(IO& io, Context& context) {
    auto links = transitions_graph::save_data::create();
    auto buffer = ParameterStorage::create();

    ParseMachine pm(io, buffer, ParseState::Type::Filename, links);
    pm.run();

    auto &service = context.getService();
    auto params = buffer.getParameters() ;
    auto result = service.save(params.filename_+".txt");

    if ( ResultType::FAILURE == result.result) {
        io.output(result.error_message+"\n");
    }
    else {
        io.output("System was saved successfully.\n");
    }

}

std::unique_ptr<CommandState> SaveCommand::change(CommandState::Type type) {
    auto command_map = CommandMap::create();
    return std::move(command_map[type]);
}
