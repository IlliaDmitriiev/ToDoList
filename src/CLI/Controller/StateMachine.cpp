//
// Created by hp on 07.09.2020.
//

#include "StateMachine.h"
#include "CLI/View/CommandStates/CommandOption.h"


StateMachine StateMachine::create(std::unique_ptr<IO> io,
                                  std::unique_ptr<Context> context,
                                  std::unique_ptr<CommandState> state)
{
    return StateMachine(std::move(io), std::move(context), std::move(state));
}

StateMachine::StateMachine(std::unique_ptr<IO> io,
                           std::unique_ptr<Context> context,
                           std::unique_ptr<CommandState> state)
                           :
                           state_(std::move(state)),
                           io_(std::move(io)),
                           context_(std::move(context))
{

}

void StateMachine::run(){

    while (true){
        state_->print( *io_);
        auto state_type = state_->read(*io_);

        if (state_type != CommandState::Type::Skip && state_type != CommandState::Type::Error)
        {
            state_->execute(*io_, *context_);
        }
        if (state_type == CommandState::Type::Error) {io_->output("Incorrect input!\n");continue;}
        if (state_type == CommandState::Type::Exit) {break;}
        state_ = state_->change(state_type);
        io_->output("*****************************************************\n");
    }

}