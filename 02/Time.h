//
// Created by Mali Abramovitch on 25/05/2023.
//

#ifndef INC_02_TIME_H
#define INC_02_TIME_H

#include <string>
#include <sstream>
#include <map>

/**
 * class for calculating the edges (weight = minutes) in the cruising time Graph
 */
class Time {
    /**
     * Date & Hour:
     * struct for representing date and time
     */
    struct Date {
        unsigned int day{};
        unsigned int month{};

        /**
         * month =1, day = 1
         */
        Date();

        explicit Date(std::string &date);
    };

    struct Hour {
        unsigned int hour{};
        unsigned int minutes{};

        /**
         * hour = 0, minute = 0
         */
        Hour();

        explicit Hour(std::string &time);
    };

    Date date;
    Hour hour;

    /**
     * <unsigned int- month, unsigned int- how many days in month>
     * for calculating the minutes between to different months
     */
    int monthsDays[13] = {0,1,2,3,4,5,6,7,8,9,10,11,12};

    /**
     * fixing the input for initialization
     * @param date
     */
    static void fixStr(std::string &date);

public:
    class TimeException : public std::exception {
        std::string mess;
    public:
        explicit TimeException(std::string &&mess);

        const char *what() const noexcept override;
    };

    Time() = default;

    /**
     * @param d = "dd/mm"
     * @param h = "HH/MM'
     */
    explicit Time(std::string d, std::string h);

    /**
     * @param dayAndHour = "dd/mm HH:MM"
     */
    explicit Time(const std::string &dayAndHour);

    ~Time() = default;

    Time(const Time &other);

    Time(Time &&) noexcept;

    Time &operator=(const Time &other);

    Time &operator=(Time &&) noexcept;

    bool operator==(const Time &other) const;

    bool operator!=(const Time &other) const;

    bool operator<(const Time &other) const;

    bool operator<=(const Time &other) const;

    bool operator>(const Time &other) const;

    bool operator>=(const Time &other) const;

    /**
     * checking if the given string is a legally format of Time - "dd/mm HH:MM"
     * @param timeStr
     */
    static void checkTimeFormat(const std::string &timeStr) noexcept(false);

    /**
     * checking if the given string is a legally format of Time - "dd/mm HH:MM"
     * @param dateStr  = "dd/mm"
     * @param hourStr = "HH:MM"
     */
    static void checkTimeFormat(const std::string &dateStr, const std::string &hourStr) noexcept(false);

    /**
     * calculating the minutes between start and end.
     * @param start
     * @param end
     * @return
     */
    friend unsigned int howLongBetween(const Time &start, const Time &end) ;

    /**
     * printing Time.
     * @param os
     * @param t
     * @return
     */
    friend std::ostream &operator<<(std::ostream &os, const Time &t);
};


#endif //INC_02_TIME_H
