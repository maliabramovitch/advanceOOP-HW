//
// Created by Mali Abramovitch on 25/05/2023.
//

#ifndef INC_02_SHIP_H
#define INC_02_SHIP_H


#include <string>
#include <deque>
#include "Time.h"

/**
 * class ship
 * class for saving the files data.
 */
class Ship {
    /**'
     * class OriginPort
     * representing the first line in the file.
     */
    struct OriginPort {
        class OriginPortException : public std::exception {
            std::string mess;
        public:
            explicit OriginPortException(const std::string &&mess);

            const char *what() const noexcept override;
        };

        std::string portName;
        Time departure;

        explicit OriginPort(const std::string &fileName) noexcept(false);

        std::ostream &printOriginPort(std::ostream &os) const;
    };

    /**
     * class DockingPort
    * representing the other lines in the file.
    */
    struct DockingPort {
        class DockingPortException : public std::exception {
            std::string mess;
        public:
            explicit DockingPortException(const std::string &&mess);

            const char *what() const noexcept override;
        };

        std::string portName;
        Time arrival, departure;
        unsigned int containersUnloaded;

        explicit DockingPort(const std::string &fileName, const std::string &line, int lineNum) noexcept(false);

        std::ostream &printDockingPort(std::ostream &os) const;

    };

    std::string fileName;
    OriginPort origin;
    std::deque<DockingPort> dockPorts;
    unsigned int containersLoaded; /// The sum of the containers unloaded during the entire sailing route.

    void checkTimeChronology();

public:
    explicit Ship(const std::string &fileName) noexcept(false);

    ~Ship() = default;

    Ship(const Ship &) = delete;

    Ship(Ship &&) = delete;

    Ship &operator=(const Ship &) = delete;

    Ship &operator=(Ship &&) = delete;

    OriginPort &getOriginPort();

    const OriginPort &getOriginPort() const;

    std::deque<DockingPort> &getDockingPorts();

    const std::deque<DockingPort> &getDockingPorts() const;

    unsigned int getContainersLoaded() const;

    std::string getFileName();

    friend std::ostream &operator<<(std::ostream &os, const Ship &ship);

};


#endif //INC_02_SHIP_H
