//
// Created by Mali Abramovitch on 08/06/2023.
//

#include "Model.h"
#include "Peasant.h"

/**
 * Work
 */
Peasant::Work::Work(shared_ptr<Structure>& f, shared_ptr<Structure>& c) : farm(f), castle(c) {}

/**
 * Peasant
 */
Peasant::Peasant(const std::string &name, double x, double y) :
        SimObject(name), Agent(name, nullptr, x, y, 5, 'P', 10) {
    tasks = make_shared<list<Work>>();
}


Peasant::~Peasant() = default;


void Peasant::loadBoxes(int boxes) {
    working = true;
    boxesCarrying = boxes;
    ++workingCircle;
}

int Peasant::unloadBoxes() {
    int tmp = boxesCarrying;
    boxesCarrying = 0;
    return tmp;
}

/*void Peasant::broadcastCurrentState() const {
    cout << "Peasant ";
    Agent::broadcastCurrentState();
    string stateStr;
    switch (state) {
        case STOP:
            stateStr = "Stopped";
            cout << ", " << stateStr;
            break;
        case DEAD:
            stateStr = "Dead";
            cout << ", " << stateStr;
            break;
        case IN_MOVEMENT:
            stateStr = "In movement";
            cout << ", " << stateStr;
            break;
    }
    //cout << ", " << stateStr;
}*/

void Peasant::update() {
    if (!tasks->empty()) {
        auto &task = tasks->front();
        if (workingCircle == 0) {
            if (state == STOP) {
                setDestination(task.farm);
                working = false;
            }
            if (*currentPosition != *task.farm) {
                startMoving();
            } else {
                ++workingCircle;
                return;
            }
            if (workingCircle == 1) {
                if (!working) {
                    int boxes = task.farm->getBoxesInStorage() > 5 ? 5 : task.farm->getBoxesInStorage();
                    loadBoxes(boxes);
                    working = true;
                    ++workingCircle;
                }
                if (workingCircle == 2) {
                    if (working) {
                        setDestination(task.castle);
                        working = false;
                    }
                    if (*currentPosition != *task.castle) {
                        startMoving();
                    } else {
                        ++workingCircle;
                    }
                }
                if (workingCircle == 3) {
                    task.castle->deposit(unloadBoxes());
                    workingCircle = 0;
                    tasks->pop_front();
                    health < 20? ++health : health;
                }
            }
        }
    }
}


void Peasant::addTask(std::shared_ptr<Structure>& farm, std::shared_ptr<Structure>& castle) {
    tasks->emplace_back(farm, castle);
}

void Peasant::wasAttacked() {
    boxesCarrying = 0;
    workingCircle = 0;
    --health;
    if (state != DEAD) {
        state = STOP;
    }
}

