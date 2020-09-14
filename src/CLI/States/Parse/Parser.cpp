//
// Created by hp on 08.09.2020.
//

#include "Parser.h"


bool Parser::parse(IO& io, Buffer& buffer, Parser::Type type) {
    bool result = false;
    if (     type == Parser::Type::Name)    {result = Parser::parseName    (io, buffer);}
    else if (type == Parser::Type::Label)   {result = Parser::parseLabel   (io, buffer);}
    else if (type == Parser::Type::Date)    {result = Parser::parseDate    (io, buffer);}
    else if (type == Parser::Type::ID)      {result = Parser::parseID      (io, buffer);}
    else if (type == Parser::Type::Priority){result = Parser::parsePriority(io, buffer);}
    return result;
}

bool Parser::parseName(IO& io, Buffer& buffer){
    io.output("Enter the name(Example of input: go to the shop tomorrow):\n");
    buffer.buf_.name_ = io.input();
    return true;
}

bool Parser::parseLabel(IO& io, Buffer& buffer){
    io.output("Enter the label(Example of input: sport):\n");
    buffer.buf_.label_ = io.input();
    return true;
}

bool Parser::parseDate(IO& io, Buffer& buffer){
    io.output("Enter the date(Example of input: 2020-02-09):\n");
    std::string date = io.input();
    boost::gregorian::date date_;
    try {
        date_ = boost::gregorian::from_string(date);
    }
    catch (...) {
        return false;
    }
    buffer.buf_.date_ = date_;
    return true;
}

bool Parser::parseID(IO& io, Buffer& buffer){
    io.output("Enter the number of task which defines it (Number > 0. Example of input: 47):\n");
    auto id = io.input();
    for(auto i: id){
        if (i>='0' && i<='9');
        else{
            return false;
        }
    }
    buffer.buf_.id_ = std::stoi(id);
    return true;
}

bool Parser::parsePriority(IO& io, Buffer& buffer){
    io.output("Enter the priority of task:\n1 - First\n2 - Second\n3 - Third\n4 - None(Example of input: 2):\n");
    auto priority = io.input();

    if (priority.size()==1 && (priority[0]>'0' && priority[0]<'5')) {
        buffer.buf_.priority_ = (TaskPriority)(std::stoi(priority) % 4);
        return true;
    }
    else {
        return false;
    }
}