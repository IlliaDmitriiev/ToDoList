//
// Created by hp on 07.09.2020.
//

#ifndef TESTCLI_STATEMACHINE_H
#define TESTCLI_STATEMACHINE_H

#include "CLI/States/Command/CommandState.h"

/*
 *  System that processes user commands
 *
 *  @author: Ilya Dmitriev
 */
class StateMachine {

public:
    static StateMachine create(
            std::unique_ptr<IO> io,
            std::unique_ptr<Context> context,
            std::unique_ptr<CommandState> state);
    /*
     * Launch processes of user command
     *
     */
    void run();

    StateMachine(const StateMachine&) = delete;
    StateMachine operator=(const StateMachine&) = delete;

private:
    StateMachine(
            std::unique_ptr<IO> io,
            std::unique_ptr<Context> context,
            std::unique_ptr<CommandState> state);

private:
    std::unique_ptr<IO> io_;
    std::unique_ptr<Context> context_;
    std::unique_ptr<CommandState> state_;

};


#endif //TESTCLI_STATEMACHINE_H
