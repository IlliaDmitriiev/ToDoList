//
// Created by illia.dmitriiev on 7/27/2020.
//

#ifndef TODOLIST_DATE_H
#define TODOLIST_DATE_H


class Date{
public:
    static  Date create(int y, int m, int d);

public:
    void CalcWeekDay();
    void moveWithinTheWeek(int diff);
    bool correctInfo();

public:
    Date(){};
    const int &getYear() const;

    const int &getMounth() const;

    const int &getDay() const;

    const int &getWday() const;

private:
    Date(int year, int mounth, int day);

private:
    int year;
    int mounth;
    int day;
    int wday;
};


#endif //TODOLIST_DATE_H
