//
// Created by hp on 08.09.2020.
//

#ifndef TESTCLI_PARSEMACHINE_H
#define TESTCLI_PARSEMACHINE_H

#include "CLI/View/ParseStates/ParseState.h"
#include <map>


/*
 *  System that parses user input.
 *
 *  @author: Ilya Dmitriev
 */

class ParseMachine {

public:
    explicit ParseMachine(
            IO&,
            ParameterStorage&,
            ParseState::Type start_state,
            std::map<ParseState::Type, ParseState::Type>&);
    /*
     * Launch parse of user input
     * by given transitions map
     *
     */
    void run();

    ParseMachine(const ParseMachine&) = delete;
    ParseMachine operator=(const ParseMachine&) = delete;

private:
    IO& io_;
    ParameterStorage& buffer_;
    std::unique_ptr<ParseState> state_;
    std::map<ParseState::Type, ParseState::Type>& next_state_;
};


#endif //TESTCLI_PARSEMACHINE_H
