//
// Created by illia.dmitriiev on 7/27/2020.
//

#ifndef TODOLIST_DATELOGIC_H
#define TODOLIST_DATELOGIC_H


#include "Date.h"
#include <iostream>

struct DateHasher{
    std::size_t operator()(const Date& k) const{
        int a = k.getDay();
        int b = k.getMounth();
        int c = k.getYear();
        return a + b * 100 + c * 10000;
    }
};

struct DateComparator{
    bool operator()( const Date& l, const Date& r ) const{
        return
                l.getYear() == r.getYear() &&
                l.getMounth()== r.getMounth() &&
                l.getDay() == r.getDay();
    }
};

#endif //TODOLIST_DATELOGIC_H
