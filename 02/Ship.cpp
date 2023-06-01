//
// Created by Mali Abramovitch on 25/05/2023.
//

#include <fstream>
#include <iostream>
#include "Ship.h"

using namespace std;

/*
 * initializing the arguments for structs C'tors
 */
bool initArgs(deque<string> &args, unsigned int lineNum) {
    try {
        stringstream ss;
        if (lineNum == 1) {
            Time::checkTimeFormat(args[1]);
            return true;
        }
        Time::checkTimeFormat(args[1]);
        Time::checkTimeFormat(args[3]);
        if (stoi(args[1]) < 0) {
            return false;
        }
        return true;
    }
    catch (Time::TimeException &e) {
        throw;
    }
}

/*
 * checking 1st line format  and calls initArgs
 */
bool checkFirstLine(const std::string &line, deque<string> &args) noexcept(false) {
    try {
        string::const_iterator start1 = line.cbegin(), start2, end1, end2 = line.cend();
        string portName, time;
        for (unsigned int i = 0; i < line.size(); ++i) {
            if (line[i] == ',') {
                end1 = start1 + i;
                start2 = end1 + 1;
                break;
            }
        }
        portName = string(start1, end1);
        time = string(start2, end2);
        if (time[time.size() - 1] == '\r' || time[time.size() - 1] == '\n') {
            time.pop_back();
        }
        if (portName.empty() || time.size() != 11) {
            return false;
        }
        args.push_back(portName);
        args.push_back(time);
        return initArgs(args, 1);
    }
    catch (exception &e) {
        throw;
    }
}

/*
 * checking 2nd line format and calls initArgs
 */
bool checkOtherLines(const std::string &line, deque<string> &args, unsigned int lineNum) noexcept(false) {
    try {
        string::const_iterator start = line.cbegin(), end;
        for (unsigned int i = 0; i < line.size(); ++i) {
            if (line[i] == ',') {
                end = line.begin() + i;
                args.emplace_back(start, end);
                start = end + 1;
            }
        }
        start = end + 1;
        end = line.cend();
        if (*(end - 1) == '\r' || *(end - 1) == '\n') {
            --end;
        }
        args.emplace_back(start, end);
        if (args.size() != 4) {
            return false;
        }
        if (args[0].empty() || args[1].size() != 11 || args[3].size() != 11) {
            return false;
        }
        int n = stoi(args[2]);
        if (n < 0) {
            return false;
        }
        return initArgs(args, lineNum);
    }
    catch (exception &e) {
        throw;
    }
}

/**
 * OriginPort
 */
Ship::OriginPort::OriginPortException::OriginPortException(const string &&mess) : mess(mess) {}

const char *Ship::OriginPort::OriginPortException::what() const noexcept {
    return mess.c_str();
}

Ship::OriginPort::OriginPort(const std::string &fileName) noexcept(false) {
    fstream file(fileName);
    stringstream ss;
    if (!file) {
        ss << "Invalid input in file " << fileName << " at line " << 0;
        throw OriginPortException(ss.str());
    }
    try {
        string line;
        getline(file, line);
        deque<string> args;
        if (!checkFirstLine(line, args)) {
            ss << "Invalid input in file " << fileName << " at line " << 1;
            throw OriginPortException(ss.str());
        }
        portName = args[0];
        departure = Time(args[1]);
    }
    catch (exception &e) {
        throw;
    }
}

std::ostream &Ship::OriginPort::printOriginPort(ostream &os) const {
    os << "\tPort Name: " << portName << endl;
    os << "\tDeparture Time: " << departure << endl;
    return os;
}
/***/


/**
 * DockingPort
 */
Ship::DockingPort::DockingPortException::DockingPortException(const string &&mess) : mess(mess) {}

const char *Ship::DockingPort::DockingPortException::what() const noexcept {
    return mess.c_str();
}

Ship::DockingPort::DockingPort(const string &fileName, const std::string &line, int lineNum) {
    deque<string> args;
    if (!checkOtherLines(line, args, lineNum)) {
        stringstream ss;
        ss << "Invalid input in file " << fileName << " at line " << lineNum;
        throw DockingPortException(ss.str());
    }
    portName = args[0];
    arrival = Time(args[1]);
    departure = Time(args[3]);
    containersUnloaded = stoi(args[2]);
}

std::ostream &Ship::DockingPort::printDockingPort(ostream &os) const {
    os << "\tPort Name: " << portName << endl;
    os << "\tArrival Time: " << arrival << endl;
    os << "\tDeparture Time: " << departure << endl;
    os << "\tContainers Unloaded: " << containersUnloaded << endl;
    return os;
}
/***/


/**
 * Ship
 */
Ship::Ship(const std::string &fileName) try: fileName(fileName), origin(fileName) {
    try {

        containersLoaded = 0;
        unsigned int lineNum = 2;
        fstream file(fileName);
        if (!file) {
            stringstream ss;
            ss << "Invalid input in file " << fileName << " at line " << 0;
            throw Ship::OriginPort::OriginPortException(ss.str());
        }
        string line;
        getline(file, line);
        while ((getline(file, line)) || !file.eof()) {
            dockPorts.emplace_back(fileName, line, lineNum);
            if (origin.departure > dockPorts[dockPorts.size() - 1].arrival) {
                stringstream ss;
                ss << "Invalid input in file " << fileName << " at line " << lineNum;
                throw DockingPort::DockingPortException(ss.str());
            }

            containersLoaded += dockPorts[dockPorts.size() - 1].containersUnloaded;
            ++lineNum;
        }
    }
    catch (exception &e) {
        throw;
    }

}
catch (exception &e) {
    throw;
}


Ship::OriginPort &Ship::getOriginPort() {
    return origin;
}

const Ship::OriginPort &Ship::getOriginPort() const {
    return origin;
}

std::deque<Ship::DockingPort> &Ship::getDockingPorts() {
    return dockPorts;
}

const std::deque<Ship::DockingPort> &Ship::getDockingPorts() const {
    return dockPorts;
}

unsigned int Ship::getContainersLoaded() const {
    return containersLoaded;
}

std::string Ship::getFileName() {
    return fileName;
}

std::ostream &operator<<(ostream &os, const Ship &ship) {
    os << "File Name: " << ship.fileName << "\n\n";
    os << "Containers Loaded: " << ship.containersLoaded << endl;
    os << "Origin Port\n";
    ship.origin.printOriginPort(os);
    os << endl;
    os << "Docking Port\n";
    for (const Ship::DockingPort &dp: ship.dockPorts) {
        dp.printDockingPort(os);
        os << endl;
    }
    return os;
}
/***/
