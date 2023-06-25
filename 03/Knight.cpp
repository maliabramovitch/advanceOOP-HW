//
// Created by Mali Abramovitch on 08/06/2023.
//

#include "Knight.h"
#include <utility>
#include <algorithm>

Knight::Knight(const std::string &name, shared_ptr<Structure> &firstDest, deque<shared_ptr<Structure>> &map) :
        Agent(name, 10, firstDest->getX(), firstDest->getY(), 'K', 20), originDestination(firstDest),
        currentDestination(firstDest), nextDestination(firstDest), map(map) {}


Knight::Knight(const Knight &rhs) :
        Agent(rhs), map(rhs.map) {
    originDestination = rhs.originDestination;
    currentDestination = rhs.currentDestination;
    nextDestination = rhs.nextDestination;
    ridingMap = rhs.ridingMap;
}

Knight &Knight::operator=(const Knight &rhs) {
    if (this != &rhs) {
        Agent::operator=(rhs);
        originDestination = rhs.originDestination;
        currentDestination = rhs.currentDestination;
        nextDestination = rhs.nextDestination;
        ridingMap = rhs.ridingMap;
    }
    return *this;
}


Knight::Knight(Knight &&lhs) noexcept: Agent(std::move(lhs)), map(lhs.map) {
    originDestination = lhs.originDestination;
    currentDestination = lhs.currentDestination;
    currentX = lhs.currentX;
    currentY = lhs.currentY;
    nextDestination = lhs.nextDestination;
    ridingMap = std::move(ridingMap);
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
        moving = lhs.moving;
        ridingMap = std::move(lhs.ridingMap);
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
    ridingMap.clear();
}

void Knight::setDestination(shared_ptr<Structure> &nexDest) {
    nextDestination = nexDest;
    MovingObject::setNewPosition(nextDestination->getX(), nextDestination->getY(), speed);
    ridingMap.clear();
    for (const auto &i: map) {
        if (*currentDestination == *i || *originDestination == *i) {
            continue;
        }
        ridingMap.push_back(i);
    }
    sort(ridingMap.begin(), ridingMap.end(), [](const shared_ptr<Structure> &s1, const shared_ptr<Structure> &s2) {
        return s1->getName() < s2->getName();
    });
    movement = DESTINATION;
    moving = true;
}

void Knight::setPosition(float newX, float newY) {
    MovingObject::setNewPosition(newX, newY, speed);
    currentDestination.reset();
    nextDestination.reset();
    originDestination.reset();
    ridingMap.clear();
    moving = true;
}

void Knight::setCourse(float newCourse) {
    MovingObject::setCourse(course, 10.0);
    currentDestination.reset();
    nextDestination.reset();
    originDestination.reset();
    ridingMap.clear();
    moving = true;
}

void Knight::broadcastCurrentState() const {
    std::cout << "Knight ";
    Agent::broadcastCurrentState();
    if (movement == DESTINATION && !stopped) {
        cout << "Heading to " << nextDestination->getName() << ", speed 10.00 km/h" << endl;
        return;
    }
}

void Knight::update() {
    if (movement == DESTINATION) {
        if (moving && currentX == newX && currentY == newY) { // reached to the next destination
            currentDestination = nextDestination;
            ridingMap.erase(std::find(ridingMap.begin(), ridingMap.end(), currentDestination));
            if (ridingMap.empty()) {// finished the patrol
                stopped = true;
                moving = false;
            } else {
                if (ridingMap.size() == 1) {
                    if (ridingMap.front() !=
                        originDestination) { // last place in the patrol before returning to the start
                        ridingMap.push_back(originDestination);
                    }
                    nextDestination = ridingMap.front();
                    MovingObject::setNewPosition(nextDestination->getX(), nextDestination->getY(), speed);
                } else {
                    float mostClosed = MAXFLOAT;
                    for (shared_ptr<Structure> &dest: ridingMap) {
                        float tmpDistance = MovingObject::calculateDistance(currentX, currentY, dest->getX(),
                                                                            dest->getY());
                        if (tmpDistance < mostClosed) {
                            MovingObject::setNewPosition(dest->getX(), dest->getY(), speed);
                            nextDestination = dest;
                            mostClosed = tmpDistance;
                        }
                    }
                }
            }
        }
    }
}

void Knight::doMove(float speed) {
    MovingObject::doMove(speed);
}


