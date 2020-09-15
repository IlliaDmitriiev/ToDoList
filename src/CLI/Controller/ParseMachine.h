//
// Created by hp on 08.09.2020.
//

#ifndef TESTCLI_PARSEMACHINE_H
#define TESTCLI_PARSEMACHINE_H

#include "CLI/States/Parse/Parser.h"
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
            Parser::Type start_state,
            std::map<Parser::Type, Parser::Type>&);
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
    Parser::Type state_;
    std::map<Parser::Type, Parser::Type>& links_;
};


#endif //TESTCLI_PARSEMACHINE_H
