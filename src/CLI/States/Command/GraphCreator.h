//
// Created by hp on 11.09.2020.
//

#ifndef TODOLIST_GRAPHCREATOR_H
#define TODOLIST_GRAPHCREATOR_H

#include "CLI/Controller/ParseMachine.h"

/*
 * Namespace which generates a transitions map
 * for each command
 *
 * @author Ilya Dmitriev
 */

namespace transitions_graph{

    namespace add_task{
        std::map<Parser::Type, Parser::Type> create(){

            std::map<Parser::Type, Parser::Type> links{
                    {Parser::Type::Name, Parser::Type::Label},
                    {Parser::Type::Label, Parser::Type::Date},
                    {Parser::Type::Date, Parser::Type::Priority},
                    {Parser::Type::Priority, Parser::Type::Exit},
            };

            return links;
        }
    }
    namespace add_subtask{
        std::map<Parser::Type, Parser::Type> create(){

            std::map<Parser::Type, Parser::Type> links{
                    {Parser::Type::ID, Parser::Type::Name},
                    {Parser::Type::Name, Parser::Type::Label},
                    {Parser::Type::Label, Parser::Type::Date},
                    {Parser::Type::Date, Parser::Type::Priority},
                    {Parser::Type::Priority, Parser::Type::Exit},
            };

            return links;
        }
    }
    namespace delete_task{
        std::map<Parser::Type, Parser::Type> create(){

            std::map<Parser::Type, Parser::Type> links{
                    {Parser::Type::ID, Parser::Type::Exit},
            };

            return links;
        }
    }
    namespace complete_task{
        std::map<Parser::Type, Parser::Type> create(){

            std::map<Parser::Type, Parser::Type> links{
                    {Parser::Type::ID, Parser::Type::Exit},
            };

            return links;
        }
    }
    namespace postpone_task{
        std::map<Parser::Type, Parser::Type> create(){

            std::map<Parser::Type, Parser::Type> links{
                    {Parser::Type::ID, Parser::Type::Date},
                    {Parser::Type::Date, Parser::Type::Exit},
            };

            return links;
        }
    }
}

#endif //TODOLIST_GRAPHCREATOR_H
