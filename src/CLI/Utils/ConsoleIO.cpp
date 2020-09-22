//
// Created by hp on 06.09.2020.
//

#include "ConsoleIO.h"
#include <iostream>

std::string ConsoleIO::input(){
    std::string in;
    getline(std::cin, in);
    return in;
}

void ConsoleIO::output(std::string out){
    std::cout << out;
}
