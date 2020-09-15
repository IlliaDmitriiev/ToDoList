//
// Created by hp on 08.09.2020.
//

#ifndef TESTCLI_PARSER_H
#define TESTCLI_PARSER_H

#include "CLI/Model/ParameterStorage.h"
#include "CLI/Utils/ConsoleIO.h"


/*
 *  Stateless object which has
 *  ability to parse input parameters
 *
 *  @author: Ilya Dmitriev
 */
class Parser{

public:
    enum class Type{
        Name,
        Label,
        Date,
        ID,
        Priority,
        Exit
    };

public:
    /*
     * Parses input parameters.
     *
     * @param: [IO] inputs param
     * @param: [ParameterStorage] saves param
     * @param: [Parser::Type] detects needed function
     *
     * @return true if parse is successful otherwise false.
     */
    static bool parse        (IO&, ParameterStorage&, Parser::Type);

private:
    static bool parseName    (IO&, ParameterStorage&);
    static bool parseLabel   (IO&, ParameterStorage&);
    static bool parseDate    (IO&, ParameterStorage&);
    static bool parseID      (IO&, ParameterStorage&);
    static bool parsePriority(IO&, ParameterStorage&);


};


#endif //TESTCLI_PARSER_H
