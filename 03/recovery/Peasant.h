//
// Created by Mali Abramovitch on 08/06/2023.
//

#ifndef INC_03_PEASANT_H
#define INC_03_PEASANT_H


#include <list>
#include <utility>
#include "Agent.h"
#include "Structure.h"


class Peasant : virtual public Agent {
    struct Work {
        shared_ptr<Structure> farm;
        shared_ptr<Structure> castle;

        Work(shared_ptr<Structure>& f, shared_ptr<Structure>& c);
    };
    int boxesCarrying = 0;
    bool working = false;
    int workingCircle = 0;
    /*
     * 0- needs to go to the farm
     * 1- needs to load boxes for 1 unit of time
     * 2- needs to go to the castle
     * 3- needs to unload the boxes in the castle
     */
    std::shared_ptr<std::list<Work>> tasks;


public:
    Peasant(const std::string& name, double x, double y);

    ~Peasant() override;

    Peasant(const Peasant &) = delete;

    Peasant(Peasant &&) = delete;

    Peasant &operator=(const Peasant &) = delete;

    Peasant &operator=(Peasant &&) = delete;

    void addTask(std::shared_ptr<Structure>& farm, std::shared_ptr<Structure>& castle);

    void loadBoxes(int boxes=5);

    int unloadBoxes();

    void wasAttacked();

    /**SimObject**/

    ///TODO- void broadcastCurrentState() const override;

    void update() override;

    void resetWorkingCircle() { workingCircle = 0; }
};


#endif //INC_03_PEASANT_H
