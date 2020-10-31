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
        static std::map<ParseState::Type, ParseState::Type> create(){

            std::map<ParseState::Type, ParseState::Type> links{
                    {ParseState::Type::Name, ParseState::Type::Label},
                    {ParseState::Type::Label, ParseState::Type::Date},
                    {ParseState::Type::Date, ParseState::Type::Priority},
                    {ParseState::Type::Priority, ParseState::Type::Exit},
            };

            return links;
        }
    }
    namespace add_subtask{
        static std::map<ParseState::Type, ParseState::Type> create(){

            std::map<ParseState::Type, ParseState::Type> links{
                    {ParseState::Type::ID, ParseState::Type::Name},
                    {ParseState::Type::Name, ParseState::Type::Label},
                    {ParseState::Type::Label, ParseState::Type::Date},
                    {ParseState::Type::Date, ParseState::Type::Priority},
                    {ParseState::Type::Priority, ParseState::Type::Exit},
            };

            return links;
        }
    }
    namespace delete_task{
        static std::map<ParseState::Type, ParseState::Type> create(){

            std::map<ParseState::Type, ParseState::Type> links{
                    {ParseState::Type::ID, ParseState::Type::Exit},
            };

            return links;
        }
    }
    namespace complete_task{
        static std::map<ParseState::Type, ParseState::Type> create(){

            std::map<ParseState::Type, ParseState::Type> links{
                    {ParseState::Type::ID, ParseState::Type::Exit},
            };

            return links;
        }
    }
    namespace postpone_task{
        static std::map<ParseState::Type, ParseState::Type> create(){

            std::map<ParseState::Type, ParseState::Type> links{
                    {ParseState::Type::ID, ParseState::Type::Date},
                    {ParseState::Type::Date, ParseState::Type::Exit},
            };

            return links;
        }
    }
    namespace edit_task{
        static std::map<ParseState::Type, ParseState::Type> create(){

            std::map<ParseState::Type, ParseState::Type> links{
                    {ParseState::Type::ID, ParseState::Type::Name},
                    {ParseState::Type::Name, ParseState::Type::Label},
                    {ParseState::Type::Label, ParseState::Type::Date},
                    {ParseState::Type::Date, ParseState::Type::Priority},
                    {ParseState::Type::Priority, ParseState::Type::Exit},
            };

            return links;
        }
    }
    namespace view_task{
        static std::map<ParseState::Type, ParseState::Type> create(){

            std::map<ParseState::Type, ParseState::Type> links{
                    {ParseState::Type::ID, ParseState::Type::Exit},
            };

            return links;
        }
    }
    namespace save_data{
        static std::map<ParseState::Type, ParseState::Type> create(){

            std::map<ParseState::Type, ParseState::Type> links{
                    {ParseState::Type::Filename, ParseState::Type::Exit},
            };

            return links;
        }
    }
    namespace load_data{
        static std::map<ParseState::Type, ParseState::Type> create(){

            std::map<ParseState::Type, ParseState::Type> links{
                    {ParseState::Type::Filename, ParseState::Type::Exit},
            };

            return links;
        }
    }
}

#endif //TODOLIST_GRAPHCREATOR_H
