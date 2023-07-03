//
// Created by Mali Abramovitch on 08/06/2023.
//

#include "Model.h"

/**
 * Work
 */
Peasant::Work::Work(const shared_ptr<Structure> &f, const shared_ptr<Structure> &c) : farm(f), castle(c) {}

Peasant::Work::~Work() {
    farm.reset();
    castle.reset();
}

/**
 * Peasant
 */
Peasant::Peasant(const std::string &name, float x, float y) :
        Agent(name, 5.0, x, y, 'P', 10) {
}


Peasant::~Peasant() {
    tasks.clear();
}

Peasant::Peasant(const Peasant &rhs) = default;

Peasant::Peasant(Peasant &&lhs) noexcept
        : Agent(std::move(lhs)), boxesCarrying(lhs.boxesCarrying), working(lhs.working),
          workingCircle(lhs.workingCircle), tasks(std::move(lhs.tasks)) {

}

Peasant &Peasant::operator=(const Peasant &rhs) {
    if (this != &rhs) {
        Agent::operator=(rhs);
        boxesCarrying = rhs.boxesCarrying;
        working = rhs.working;
        workingCircle = rhs.workingCircle;
        tasks = rhs.tasks;
    }
    return *this;
}

Peasant &Peasant::operator=(Peasant &&lhs) noexcept {
    if (this != &lhs) {
        Agent::operator=(std::move(lhs));
        boxesCarrying = lhs.boxesCarrying;
        working = lhs.working;
        workingCircle = lhs.workingCircle;
        tasks = std::move(lhs.tasks);
        lhs.boxesCarrying = 0;
        lhs.working = false;
        lhs.workingCircle = 0;
    }
    return *this;
}


void Peasant::loadBoxes(int boxes) {
    working = true;
    boxesCarrying = boxes;
}

int Peasant::unloadBoxes() {
    int tmp = boxesCarrying;
    boxesCarrying = 0;
    return tmp;
}

void Peasant::broadcastCurrentState() const {
    cout << "Peasant ";
    Agent::broadcastCurrentState();
    if (isAlive && movement == DESTINATION) {
        switch (workingCircle) {
            case 0: {
                cout << "Heading to " << tasks.front()->farm->getName() << ", speed 5.00 km/h" << endl;
                break;
            }
            case 1: {
                cout << "Loading Boxes at " << tasks.front()->farm->getName() << endl;
                break;
            }
            case 2: {
                cout << "Heading to " << tasks.front()->castle->getName() << endl;
                break;
            }
            case 3: {
                cout << "Unloading Boxes at " << tasks.front()->castle->getName() << endl;
                break;
            }

        }
    }
}

void Peasant::update() {
    if (isAlive && !stopped) {
        if (!working) {
            if (!tasks.empty()) {
                auto &task = tasks.front();
                MovingObject::setNewPosition(task->farm->getX(), task->farm->getY(), speed);
                movement = DESTINATION;
                working = true;
            } else { return; }
        } else {
            auto &task = tasks.front();
            if (workingCircle == WALKING_TO_THE_FARM && currentX == task->farm->getX() &&
                currentY == task->farm->getY()) {
                ++workingCircle;
                justFinishedWalking = true;
            } else if (workingCircle == LOADING_BOXES_IN_THE_FARM) {
                loadBoxes(task->farm->withdraw());
                ++workingCircle;
                setNewPosition(task->castle->getX(), task->castle->getY(), speed);
                movement = DESTINATION;
            } else if (workingCircle == WALKING_TO_THE_CASTLE && currentX == task->castle->getX() &&
                       currentY == task->castle->getY()) {
                ++workingCircle;
                task->castle->deposit(unloadBoxes());
            } else if (workingCircle == UNLOADING_BOXES_IN_THE_CASTLE) {
                workingCircle = 0;
                tasks.pop_front();
                working = false;
                if (tasks.empty()) {
                    stopped = true;
                }
                movement = STOPPED;
            }
        }
    }
}

void Peasant::doMove() {
    if (isAlive && (workingCircle == WALKING_TO_THE_FARM || workingCircle == WALKING_TO_THE_CASTLE)) {
        MovingObject::doMove();
        if (getDistanceFromDestination() != 0) {
            justFinishedWalking = true;
        }
    }
}

void Peasant::addTask(const std::shared_ptr<Structure> &farm, const std::shared_ptr<Structure> &castle) {
    if (isAlive) {
        tasks.push_back(make_shared<Work>(farm, castle));
        stopped = false;
        if (!working) {
            MovingObject::setNewPosition(farm->getX(), farm->getY(), speed);
            movement = DESTINATION;
            working = true;
        }
    }
}

void Peasant::wasAttacked(bool win) {
    --health;
    if (health == 0) {
        isAlive = false;
    }
    if (!win) {
        resetWorkingCircle();
        stopped = true;
    }
}


