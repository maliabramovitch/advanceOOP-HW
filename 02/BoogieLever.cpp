//
// Created by Mali Abramovitch on 25/05/2023.
//

#include <fstream>
#include <utility>
#include "BoogieLever.h"
#include "Time.h"

using namespace std;

void BoogieLever::updateContainerGraph(const Ship &ship) {
    for (const auto &dockPort: ship.getDockingPorts()) {
        containers.updateEdge(ship.getOriginPort().portName, dockPort.portName,
                              (containers(ship.getOriginPort().portName, dockPort.portName)) +
                              (dockPort.containersUnloaded));
    }

}

void BoogieLever::updateTravelingGraph(const Ship &ship) {
    auto &originPort = ship.getOriginPort();
    auto &dockingPorts = ship.getDockingPorts();
    if (cruiseTime.isEdgeExist(originPort.portName, dockingPorts[0].portName)) { //the edge does exist
        double prevEdge = cruiseTime(originPort.portName, dockingPorts[0].portName);
        double newEdge = howLongBetween(originPort.departure, dockingPorts[0].arrival);
        cruiseTime.updateEdge(originPort.portName, dockingPorts[0].portName, (prevEdge + newEdge) / 2);
    } else { //the edge does not exist
        cruiseTime.addEdge(originPort.portName, dockingPorts[0].portName,
                              howLongBetween(originPort.departure, dockingPorts[0].arrival));
    }
    for (unsigned int i = 0; i < ship.getDockingPorts().size() - 1; ++i) {
        if (cruiseTime.isEdgeExist(dockingPorts[i].portName, dockingPorts[i + 1].portName)) { //the edge does exist
            double prevEdge = cruiseTime(dockingPorts[i].portName, dockingPorts[i + 1].portName);
            double newEdge = howLongBetween(dockingPorts[i].departure, dockingPorts[i + 1].arrival);
            cruiseTime.updateEdge(dockingPorts[i].portName, dockingPorts[i + 1].portName, (prevEdge + newEdge) / 2);
        } else { //the edge does exist
            cruiseTime.addEdge(dockingPorts[i].portName, dockingPorts[i + 1].portName,
                                  howLongBetween(dockingPorts[i].departure, dockingPorts[i + 1].arrival));
        }

    }

}

BoogieLever::BoogieLever(const std::deque<std::string> &inFilesNames, std::string outFileName) : outFileName(std::move(
        outFileName)), containers(0), cruiseTime(0) {
    try {
        for (const string &inFileName: inFilesNames) {
            ships.emplace_back(inFileName);
            updateTravelingGraph(ships[ships.size() - 1]);
            updateContainerGraph(ships[ships.size() - 1]);
        }
    }
    catch (exception &e) {
        throw;
    }
}

void BoogieLever::load(const std::string &fileName) {
    try {
        fstream file(fileName);
        if (!file) {
            cerr << "ERROR opening/reading the specified file." << endl;
            return;
        }
        file.close();
        ships.emplace_back(fileName);
        updateTravelingGraph(ships[ships.size() - 1]);
        updateContainerGraph(ships[ships.size() - 1]);
        cout << "Update was successful.\n";
    }
    catch (exception &e) {
        cerr << e.what();
    }
}

void BoogieLever::outbound(const std::string &port) {
    if (!cruiseTime.isVertexExist(port)) {
        cerr << port << "does not exist in the database." << endl;
        return;
    }
    auto outBound = cruiseTime.getOutGoingVertices(port);
    if (outBound.empty()) {
        cout << port << ": " << "no outbound ports" << endl;
    } else {
        for (const string &outPort: outBound) {
            cout << outPort << ',' << cruiseTime(port, outPort) << endl;
        }
    }
}

void BoogieLever::inbound(const std::string &port) {
    if (!cruiseTime.isVertexExist(port)) {
        cerr << port << " does not exist in the database." << endl;
        return;
    }
    auto inBound = cruiseTime.getInGoingVertices(port);
    if (inBound.empty()) {
        cout << port << ": " << " no inbound ports" << endl;
    } else {
        for (const string &inPort: inBound) {
            cout << inPort << ',' << cruiseTime(inPort, port) << endl;
        }
    }
}

int BoogieLever::balanceHelper(const std::string &port, const Time &&time) {
    int balance = 0;
    for (auto &ship: ships) {
        if (ship.getOriginPort().portName == port) {
            if (ship.getOriginPort().departure <= time) {
                balance -= ship.getContainersLoaded();
            }
        }
        for (const auto &dockingPort: ship.getDockingPorts()) {
            if (dockingPort.portName == port) {
                if (dockingPort.arrival <= time) {
                    balance += dockingPort.containersUnloaded;
                }
            }
        }
    }
    return balance;
}

void BoogieLever::balance(const std::string &port, const std::string &date, const std::string &time) {
    try {
        if (!cruiseTime.isVertexExist(port)) {
            cerr << port << "does not exist in the database." << endl;
            return;
        }
        Time::checkTimeFormat(date, time);
        int balance = balanceHelper(port, Time(date, time));
        cout << balance << endl;
    }
    catch (exception &e) {
        throw;
    }
}

void BoogieLever::print() {
    fstream file(outFileName, ios_base::out);
    if (!file) {
        cerr << "ERROR opening/writing the specified file." << endl;
        return;
    }
    file << "Edge = (row, col)\n\n";
    file << "Containers Graph:\n" << containers << "\n";
    file << "Cruising Time Graph in *MINUTES*:\n" << cruiseTime << '\n';
}
