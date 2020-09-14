//
// Created by hp on 08.09.2020.
//

#ifndef TESTCLI_PARSER_H
#define TESTCLI_PARSER_H

#include "CLI/Model/Buffer.h"
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
     * @param: [Buffer] saves param
     * @param: [Parser::Type] detects needed function
     *
     * @return true if parse is successful otherwise false.
     */
    static bool parse        (IO&, Buffer&, Parser::Type);

private:
    static bool parseName    (IO&, Buffer&);
    static bool parseLabel   (IO&, Buffer&);
    static bool parseDate    (IO&, Buffer&);
    static bool parseID      (IO&, Buffer&);
    static bool parsePriority(IO&, Buffer&);


};


#endif //TESTCLI_PARSER_H
