//
// Created by Mali Abramovitch on 25/05/2023.
//

#ifndef INC_02_BOOGIELEVER_H
#define INC_02_BOOGIELEVER_H

#include "DirectedGraph.h"
#include "Ship.h"


/**
 * the data base.
 */
class BoogieLever {
    std::string outFileName;
    DirectedGraph<std::string, int> containers;
    DirectedGraph<std::string, double> cruiseTime;
    std::deque<Ship> ships;

    /**
     * updating cruiseTime Graph by the data from (Ship)ship
     * @param ship
     */
    void updateTravelingGraph(const Ship &ship);

    /**
    * updating containers Graph by the data from (Ship)ship
    * @param ship
    */
    void updateContainerGraph(const Ship &ship);

    /**
     * calculating the balance.
     * @param port
     * @param time
     * @return
     */
    int balanceHelper(const std::string &port, const Time &&time);

public:
    explicit BoogieLever(const std::deque<std::string> &inFilesNames, std::string outFileName) noexcept(false);

    void load(const std::string &fileName);

    void outbound(const std::string &port);

    void inbound(const std::string &port);

    void balance(const std::string &port, const std::string &date, const std::string &time) noexcept(false);

    void print();
};


#endif //INC_02_BOOGIELEVER_H
