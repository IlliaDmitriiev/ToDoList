//
// Created by hp on 15.09.2020.
//

#include "ParseDate.h"


bool ParseDate::read(IO& io, ParameterStorage& buffer) {
    std::string date = io.input();
    boost::gregorian::date date_;
    try {
        date_ = boost::gregorian::from_string(date);
    }
    catch (...) {
        return false;
    }
    buffer.getParameters().date_ = date_;
    return true;
}

void ParseDate::print(IO& io) {
    io.output("Enter the date(Example of input: 2020-02-09):\n");
}

ParseState::Type ParseDate::changeState() {
    return ParseState::Type::Date;
}
