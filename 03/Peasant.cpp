//
// Created by Mali Abramovitch on 08/06/2023.
//

#include "Model.h"
#include "Peasant.h"

/**
 * Work
 */
Peasant::Work::Work(weak_ptr<Structure> &f, weak_ptr<Structure> &c) : farm(f), castle(c) {}

Peasant::Work::~Work() {
    farm.reset();
    castle.reset();
}

/**
 * Peasant
 */
Peasant::Peasant(const std::string &name, float x, float y) :
        Agent(name, 5.0 ,x, y, 'P', 10) {
    tasks = make_shared<list<Work>>();
}


Peasant::~Peasant() {
    tasks->clear();
    tasks.reset();
}

Peasant::Peasant(const Peasant & rhs) = default;

Peasant::Peasant(Peasant &&lhs)  noexcept
: Agent(std::move(lhs)), boxesCarrying(lhs.boxesCarrying), working(lhs.working), workingCircle(lhs.workingCircle), tasks(std::move(lhs.tasks))  {

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
        Agent::operator=(lhs);
        boxesCarrying = lhs.boxesCarrying;
        working = lhs.working;
        workingCircle = lhs.workingCircle;
        tasks = std::move(lhs.tasks);
        lhs.boxesCarrying =0;
        lhs.working = false;
        lhs.workingCircle = 0;
        lhs.name = "";
        lhs.role = 'A';
        lhs.health = 0;
        lhs.isAlive = false;
    }
    return *this;
}


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

void Peasant::broadcastCurrentState() const {
    cout << "Peasant ";
    Agent::broadcastCurrentState();
    if (!isAlive) {
        cout << "Dead" << endl;
    }
    if (stopped) {
        cout << "Stopped" << endl;
    } else {
        switch (workingCircle) {
            case 0:
                cout << "Heading to " << tasks->front().farm.lock()->getName() << ", speed 5.00 km/h" <<endl;
                break;
            case 2:
                cout << "Heading to " << tasks->front().castle.lock()->getName() << endl;
        }
    }
}

void Peasant::update() {
    if (!tasks->empty()) {
        auto &task = tasks->front();
        if (workingCircle == 0) {
            if (stopped) {
                setNewPosition(task.farm.lock()->getX(), task.farm.lock()->getY(), speed);
                working = false;
            }
            if (!stopped) {
                MovingObject::move(speed);
            } else {
                ++workingCircle;
                return;
            }
            if (workingCircle == 1) {
                if (!working) {
                    int boxes = task.farm.lock()->getBoxesInStorage() > 5 ? 5 : task.farm.lock()->getBoxesInStorage();
                    loadBoxes(boxes);
                    working = true;
                    ++workingCircle;
                }
                if (workingCircle == 2) {
                    if (working) {
                        setNewPosition(task.castle.lock()->getX(), task.castle.lock()->getY(),speed);
                        working = false;
                    }
                    if (!stopped) {
                        MovingObject::move(speed);
                    } else {
                        ++workingCircle;
                    }
                }
                if (workingCircle == 3) {
                    task.castle.lock()->deposit(unloadBoxes());
                    resetWorkingCircle();
                    tasks->pop_front();
                    if (health < 20) ++health;
                }
            }
        }
    }
}


void Peasant::addTask(std::weak_ptr<Structure> &farm, std::weak_ptr<Structure> &castle) {
    tasks->emplace_back(farm, castle);
}

void Peasant::wasAttacked() {
    resetWorkingCircle();
    --health;
    if (isAlive) {
        stopped = true;
    }
}


