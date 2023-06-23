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
        weak_ptr<Structure> farm;
        weak_ptr<Structure> castle;

        Work(weak_ptr<Structure> &f, weak_ptr<Structure> &c);

        ~Work();
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
    Peasant(const std::string &name, float x, float y);

    ~Peasant() ;

    Peasant(const Peasant &rhs);

    Peasant(Peasant &&lhs) noexcept;

    Peasant &operator=(const Peasant &rhs);

    Peasant &operator=(Peasant &&lhs) noexcept;

    void addTask(std::weak_ptr<Structure> &farm, std::weak_ptr<Structure> &castle);

    void loadBoxes(int boxes);

    int unloadBoxes();

    void wasAttacked();

    void resetWorkingCircle() {
        workingCircle = 0;
        boxesCarrying = 0;
    }

    void broadcastCurrentState() const override;

    void update() override;
};


#endif //INC_03_PEASANT_H
