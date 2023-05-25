//
// Created by Mali Abramovitch on 25/05/2023.
//

#include "Time.h"
#include <iomanip>
#include <iostream>

using namespace std;

Time::Date::Date(std::string &date) {
    std::stringstream ss;
    fixStr(date);
    ss << date;
    ss >> day;
    ss >> month;
}


Time::Hour::Hour(std::string &time) {
    std::stringstream ss;
    fixStr(time);
    ss << time;
    ss >> hour;
    ss >> minutes;
}

Time::Time(std::string d, std::string h) : date(d), hour(h) {
    initMonthsDays();
}

unsigned int howLongBetween(const Time &start, const Time &end) {
    unsigned int hours = (end.hour.hour - start.hour.hour) * 60,
            minutes = (end.hour.minutes - start.hour.minutes), days;
    if (start.date.month == end.date.month) {
        days = (end.date.day - start.date.day);
    } else { // not the same month
        for (unsigned int i = (start.date.month + 1) % 12; i != end.date.month; ((++i) % 12)) {
            days += end.monthsDays.at(i);
        }
        days += start.monthsDays.at(start.date.month) - start.date.day;
        days += end.date.day;
    }
    return (days * 24 * 60) + hours + minutes;
}

std::ostream &operator<<(std::ostream &os, const Time &t) {
    string day, month, hour, min;
    if (t.date.day < 10) os << '0';
    os << t.date.day << '/';
    if (t.date.month < 10) os << '0';
    os << t.date.month << ' ';
    if (t.hour.hour < 10) os << '0';
    os << t.hour.hour << ':';
    if (t.hour.minutes < 10) os << '0';
    os << t.hour.minutes << endl;
    return os;
}

void Time::initMonthsDays() {
    monthsDays[1] = 31;
    monthsDays[2] = 28;
    monthsDays[3] = 31;
    monthsDays[4] = 30;
    monthsDays[5] = 31;
    monthsDays[6] = 30;
    monthsDays[7] = 31;
    monthsDays[8] = 31;
    monthsDays[9] = 30;
    monthsDays[10] = 31;
    monthsDays[11] = 30;
    monthsDays[12] = 31;
}

void Time::fixStr(string &d) {
    for (char &s: d) {
        if (!isdigit(s)) s = ' ';
    }
}
