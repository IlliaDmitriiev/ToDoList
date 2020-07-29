//
// Created by illia.dmitriiev on 7/27/2020.
//

#include "Date.h"
#include <iostream>


Date Date::create(int y, int m, int d){
    Date date(y, m, d);
    if (!date.correctInfo())
        throw std::runtime_error("Incorrect date");
    date.CalcWeekDay();
    return date;
}

void Date::CalcWeekDay(){
    int m = mounth;
    int y = year;
    if (m < 3){
        m += 10;
        --y;
    }
    else m -= 2;
    int   N = day + (31 * m) / 12 + y
              + y / 4 - y / 100 + y / 400;
    wday = N % 7;
}

void Date::moveWithinTheWeek(int diff){
    bool leapYear = false;
    if (year%400 ==0 || (year%100!=0 && year%4 ==0))
        leapYear = true;
    int a[12] = {31, 28, 31, 30, 31,
                 30, 31, 31, 30, 31, 30, 31};
    if (leapYear)
        a[1]++;
    if (diff == 0) return;
    else if (diff > 0){
        day +=diff;
        if (a[mounth - 1] >= day) {CalcWeekDay(); return;}
        day -= a[mounth - 1];
        mounth++;
        if (mounth > 12) {mounth = 1; year++;}
        CalcWeekDay();
    }
    else {
        day+=diff;
        if (day > 0){ CalcWeekDay(); return; }
        mounth--;
        day += a[mounth - 1];
        if (mounth < 1) {mounth = 12; year--;}
        CalcWeekDay();
    }

}
bool Date::correctInfo(){
    bool leapYear = false;
    if (year%400 ==0 || (year%100!=0 && year%4 ==0))
        leapYear = true;
    if (mounth>12 || mounth<1)
        return false;
    int a[12] = {31, 28, 31, 30, 31,
                 30, 31, 31, 30, 31, 30, 31};

    if (leapYear)
        a[1]++;
    if (a[mounth - 1]>=day && day > 0)
        return true;
    else
        return false;
}

const int &Date::getYear() const {
    return year;
}

const int &Date::getMounth() const {
    return mounth;
}

const int &Date::getDay() const {
    return day;
}

const int &Date::getWday() const {
    return wday;
}

Date::Date(int year, int mounth, int day)
        :year(year), mounth(mounth), day(day) {}


