//
// Created by Mali Abramovitch on 08/06/2023.
//

#include "Knight.h"
#include <utility>
#include <algorithm>


bool Knight::Comparator::operator()(const weak_ptr<Structure> &dest1, const weak_ptr<Structure> &dest2) {
    float sub1 = dest1.lock()->getX() - myDest.lock()->getX();
    float sub2 = dest1.lock()->getY() - myDest.lock()->getY();
    float d1 = sqrt((pow(sub1, 2) + pow(sub2, 2)));
    float sub3 = dest2.lock()->getX() - myDest.lock()->getX();
    float sub4 = dest2.lock()->getY() - myDest.lock()->getY();
    float d2 = sqrt((pow(sub3, 2) + pow(sub4, 2)));
    if (d1 == d2) {
        return dest1.lock()->getName() < dest2.lock()->getName();
    }
    return d1 < d2;
}

void Knight::sortRidingMap(const weak_ptr<Structure> &myDest) {
    if (ridingMap.empty()) {
        for (const auto &i: map) {
            if (*currentDestination.lock() == *i.lock() || *originDestination.lock() == *i.lock()) {
                continue;
            }
            ridingMap.push_back(i);
        }
    }
    std::sort(ridingMap.begin(), ridingMap.end(), Comparator(myDest));
}


Knight::Knight(const std::string &name, weak_ptr<Structure> &firstDest, deque<weak_ptr<Structure>> &map) :
        Agent(name, 10, firstDest.lock()->getX(), firstDest.lock()->getY(), 'K', 20), originDestination(firstDest),
        currentDestination(firstDest), nextDestination(firstDest), map(map) {}


Knight::Knight(const Knight &rhs) :
        Agent(rhs), map(rhs.map) {
    originDestination = rhs.originDestination;
    currentDestination = rhs.currentDestination;
    nextDestination = rhs.nextDestination;
}

Knight &Knight::operator=(const Knight &rhs) {
    if (this != &rhs) {
        Agent::operator=(rhs);
        originDestination = rhs.originDestination;
        currentDestination = rhs.currentDestination;
        nextDestination = rhs.nextDestination;
    }
    return *this;
}


Knight::Knight(Knight &&lhs) noexcept: Agent(std::move(lhs)), map(lhs.map) {
    originDestination = lhs.originDestination;
    currentDestination = lhs.currentDestination;
    currentX = lhs.currentX;
    currentY = lhs.currentY;
    nextDestination = lhs.nextDestination;
    lhs.originDestination.reset();
    lhs.currentDestination.reset();
    lhs.nextDestination.reset();
}

Knight &Knight::operator=(Knight &&lhs) noexcept {
    if (this != &lhs) {
        Agent::operator=(lhs);
        originDestination = lhs.originDestination;
        originDestination = lhs.originDestination;
        currentDestination = lhs.currentDestination;
        nextDestination = lhs.nextDestination;
        lhs.originDestination.reset();
        lhs.currentDestination.reset();
        lhs.nextDestination.reset();
        lhs.name = "";
        lhs.role = 'A';
        lhs.health = 0;
        lhs.isAlive = false;
    }
    return *this;
}

Knight::~Knight() {
    originDestination.reset();
    currentDestination.reset();
    nextDestination.reset();
}

void Knight::setDestination(weak_ptr<Structure> &nexDest) {
    destination = true;
    nextDestination = nexDest;
    setNewPosition(nextDestination.lock()->getX(), nextDestination.lock()->getY(), speed);
    sortRidingMap(nextDestination);
    moving = true;
}

void Knight::setPosition(float newX, float newY) {
    destination = false;
    setNewPosition(newX, newY, speed);
    currentDestination.reset();
    nextDestination.reset();
    originDestination.reset();
    moving = true;
}

void Knight::setCourse(float newCourse) {
    destination = false;
    MovingObject::setCourse(course, 10.0);
    currentDestination.reset();
    nextDestination.reset();
    originDestination.reset();
    moving = true;
}

void Knight::broadcastCurrentState() const {
    std::cout << "Knight ";
    Agent::broadcastCurrentState();
    if (stopped && !moving) {
        cout << "Stopped" << endl;
    } else {
        if (destination) {
            cout << "Heading to " << nextDestination.lock()->getName() << ", speed 10.00 km/h" << endl;
            return;
        }
        if (position) {
            cout << "Heading to (" << getNewX() << ", " << getNewY() << "), ";
            cout << "speed " << speed << " km/h" << endl;

        } else {
            cout << "Heading on course " << course << " deg, speed 10.00 km/h" << endl;
        }
    }

}

void Knight::update() {
    move(speed);
}

void Knight::move(float speed) {
    if (stopped) { //reached to the next destination
        if (moving) {
            if (destination) {
                if (ridingMap.size() == 1 && *ridingMap.front().lock() != *originDestination.lock()) {
                    ridingMap.push_back(originDestination);
                }
                currentDestination = ridingMap.front();
                ridingMap.pop_front();
                if (ridingMap.empty()) {
                    stopped = true;
                    moving = false;
                } else {
                    setDestination(ridingMap.front());
                }
            }
            if (position) {
                float minDistance = MAXFLOAT;
                for (auto &structure: map) {
                    float dis = MovingObject::calculateDistance(getCurrentX(), getCurrentY(), structure.lock()->getX(),
                                                                structure.lock()->getY());
                    if (dis < minDistance) {
                        minDistance = dis;
                        originDestination = structure;
                    }
                    sortRidingMap(originDestination);
                    setDestination(nextDestination);
                }
            }
        } else {
            return;
        }
    }
    MovingObject::move(speed);
}


