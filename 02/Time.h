//
// Created by Mali Abramovitch on 25/05/2023.
//

#ifndef INC_02_TIME_H
#define INC_02_TIME_H

#include <string>
#include <sstream>
#include <map>


class Time {
    struct Date {
        unsigned int day{};
        unsigned int month{};

        explicit Date(std::string &d);
    };

    struct Hour {
        unsigned int hour{};
        unsigned int minutes{};

        explicit Hour(std::string &time);
    };

    Date date;
    Hour hour;
    std::map<unsigned int, unsigned int> monthsDays;
    void initMonthsDays();
    static void fixStr(std::string& date);

public:
    Time(std::string d, std::string h);
    ~Time() = default;
    Time(const Time&) = default;
    Time(Time&&) = delete;
    Time& operator=(const Time&) = default;
    Time& operator=(Time&&) = delete;

    friend unsigned int howLongBetween(const Time &start, const Time &end);
    friend std::ostream& operator<<(std::ostream& os, const Time& t);
};


#endif //INC_02_TIME_H
