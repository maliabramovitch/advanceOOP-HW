//
// Created by Mali Abramovitch on 25/05/2023.
//

#include "Time.h"
#include <iostream>

using namespace std;

/**
 * Date
 */

Time::Date::Date() : day(1), month(1) {}

Time::Date::Date(std::string &date) {
    std::stringstream ss;
    fixStr(date);
    ss << date;
    ss >> day;
    ss >> month;
    if (day < 1 || day > 31) {
        throw TimeException("illigle Date");
    }
    if (month < 1 || month > 12) {
        throw TimeException("illigle Date");
    }
    if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30) {
        throw TimeException("illigle Date");
    }
    if (month == 2 && day > 28) {
        throw TimeException("illigle Date");
    }
}

/**
 * Hour
 */

Time::Hour::Hour() : hour(0), minutes(0) {}

Time::Hour::Hour(std::string &time) {
    std::stringstream ss;
    fixStr(time);
    ss << time;
    ss >> hour;
    ss >> minutes;
    if (hour < 0 || hour > 24) {
        throw TimeException("illigle hour");
    }
    if (minutes < 0 || minutes > 59) {
        throw TimeException("illigle hour");
    }
}


/**
 * Time
 */
Time::Time(std::string d, std::string h) : date(d), hour(h) {
}


Time::Time(const std::string &dayAndHour) {
    auto strIt = dayAndHour.begin();
    for (; strIt != dayAndHour.end(); ++strIt) {
        if (*strIt == ' ') {
            break;
        }
    }
    string dateStr(dayAndHour.begin(), strIt), hourStr(strIt + 1, dayAndHour.end());
    date = Date(dateStr);
    hour = Hour(hourStr);
}

Time::Time(const Time &other) {
    *this = other;
}

Time::Time(Time &&other) noexcept {
    *this = other;
}

Time &Time::operator=(const Time &other) {
    if (this != &other) {
        date.month = other.date.month;
        date.day = other.date.day;
        hour.hour = other.hour.hour;
        hour.minutes = other.hour.minutes;
    }
    return *this;
}

Time &Time::operator=(Time &&other) noexcept {
    if (this != &other) {
        date.month = other.date.month;
        date.day = other.date.day;
        hour.hour = other.hour.hour;
        hour.minutes = other.hour.minutes;
        other.date.month = 0;
        other.date.day = 0;
        other.hour.hour = 0;
        other.hour.minutes = 0;
    }
    return *this;
}

unsigned int howLongBetween(const Time &start, const Time &end) {
    if (start.date.month > end.date.month) {
        throw Time::TimeException("start month > end month");
    }
    unsigned int hours = (end.hour.hour - start.hour.hour) * 60,
            minutes = (end.hour.minutes - start.hour.minutes), days;
    if (start.date.month == end.date.month) {
        days = (end.date.day - start.date.day) * 24 * 60;
    } else { // not the same month
        for (unsigned int i = (start.date.month + 1); i != end.date.month; ++i) {
            days += end.monthsDays[i];
        }
        days += start.monthsDays[start.date.month] - start.date.day;
        days += end.date.day;
        days *= 24 * 60;
    }
    return days + hours + minutes;
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
    os << t.hour.minutes;
    return os;
}

void Time::fixStr(string &d) {
    for (char &s: d) {
        if (!isdigit(s)) s = ' ';
    }
}

bool Time::operator==(const Time &other) const {
    return date.month == other.date.month && date.day == other.date.day && hour.hour == other.hour.hour &&
           hour.minutes == other.hour.minutes;
}

bool Time::operator!=(const Time &other) const {
    return !operator==(other);
}

bool Time::operator<(const Time &other) const {
    if (date.month < other.date.month) {
        return true;
    }
    if (date.month == other.date.month) {
        if (date.day < other.date.day) {
            return true;
        }
        if (date.day == other.date.day) {
            if (hour.hour < other.hour.hour) {
                return true;
            }
            if (hour.hour == other.hour.hour) {
                if (hour.minutes < other.hour.minutes) {
                    return true;
                }
                return false;
            }
            return false;
        }
        return false;
    }
    return false;
}

bool Time::operator>(const Time &other) const {
    return !operator<(other);
}

void Time::checkTimeFormat(const string &time) {
    stringstream ss;
    ss << time;
    string dateStr, hourStr;
    ss >> dateStr;
    ss >> hourStr;
    if (dateStr.size() != 5 || hourStr.size() != 5) {
        throw TimeException("illegible time format");
    }
    for (int i = 0; i < 5; ++i) {
        if ((isdigit(dateStr[i]) && !isdigit(hourStr[i])) || (!isdigit(dateStr[i]) && isdigit(hourStr[i]))) {
            throw TimeException("illegible time format");
        }
        if ((dateStr[i] == '/' && hourStr[i] != ':') || (dateStr[i] != '/' && hourStr[i] == ':')) {
            throw TimeException("illegible time format");
        }
    }
}

bool Time::operator<=(const Time &other) const {
    return (operator<(other) | operator==(other));
}

bool Time::operator>=(const Time &other) const {
    return (operator>(other) | operator==(other));
}

void Time::checkTimeFormat(const string &dateStr, const string &hourStr) noexcept(false) {
    try {
        string time(dateStr + " " + hourStr);
        checkTimeFormat(time);
    }
    catch (exception &e) {
        throw;
    }
}

/**
 * TimeException
 */
Time::TimeException::TimeException(string &&mess) : mess(mess) {}

const char *Time::TimeException::what() const noexcept {
    return mess.c_str();
}
/***/