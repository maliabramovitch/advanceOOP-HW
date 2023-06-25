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

        Work(shared_ptr<Structure> farm, shared_ptr<Structure> castle);
        ~Work();
    };

    int boxesCarrying = 0;
    bool working = false;
    enum {WALKING_TO_THE_FARM=0, LOADING_BOXES_IN_THE_FARM =1 , WALKING_TO_THE_CASTLE = 2, UNLOADING_BOXES_IN_THE_CASTLE};
    int workingCircle = 0;
    /*
     * 0- needs to go to the farm
     * 1- needs to load boxes for 1 unit of time
     * 2- needs to go to the castle
     * 3- needs to unload the boxes in the castle
     */
    std::list<shared_ptr<Work>> tasks;

public:
    Peasant(const std::string &name, float x, float y);

    ~Peasant() ;

    Peasant(const Peasant &rhs);

    Peasant(Peasant &&lhs) noexcept;

    Peasant &operator=(const Peasant &rhs);

    Peasant &operator=(Peasant &&lhs) noexcept;

    void addTask(const std::shared_ptr<Structure>& farm, const std::shared_ptr<Structure>& castle);

    void loadBoxes(int boxes);

    int unloadBoxes();

    void wasAttacked(bool win);

    void resetWorkingCircle() {
        workingCircle = 0;
        boxesCarrying = 0;
        tasks.clear();
        working = false;
    }

    void doMove(float newSpeed) override;

    void broadcastCurrentState() const override;

    void update() override;
};


#endif //INC_03_PEASANT_H
