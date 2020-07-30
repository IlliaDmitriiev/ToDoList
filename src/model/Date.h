//
// Created by illia.dmitriiev on 7/27/2020.
//

#ifndef TODOLIST_DATE_H
#define TODOLIST_DATE_H

#include <iostream>

class Date{
public:
    static  Date create(int y, int m, int d);

public:
    static void Print(const Date& date);

public:
    struct Hasher{
        std::size_t operator()(const Date& k) const{
            int a = k.getDay();
            int b = k.getMounth();
            int c = k.getYear();
            return a + b * 100 + c * 10000;
        }
    };

    struct Comparator{
        bool operator()( const Date& l, const Date& r ) const{
            return
                    l.getYear() == r.getYear() &&
                    l.getMounth()== r.getMounth() &&
                    l.getDay() == r.getDay();
        }
    };

public:
    void CalcWeekDay();
    void moveWithinTheWeek(int diff);
    bool correctInfo();

public:
    int getYear() const;

    int getMounth()const;

    int getDay() const;

    int getWday() const;

private:
    Date(int year, int mounth, int day);

private:
    int year;
    int mounth;
    int day;
    int wday;
};


#endif //TODOLIST_DATE_H
