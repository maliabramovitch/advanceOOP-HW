//
// Created by Mali Abramovitch on 08/06/2023.
//

#ifndef INC_03_AGENT_H
#define INC_03_AGENT_H

#include <utility>
#include <iostream>
#include <sstream>
#include "MovingObject.h"
#include "Model.h"
#include <cmath>

class Agent : public SimObject, public MovingObject {
protected:
    char role = 'A'; /// P = peasant/T = Thug/K = knight
    int health = 20;
    bool isAlive = true;

public:
    Agent(const std::string &name, int speed, float x, float y, char role, int health) :
            SimObject(name), MovingObject(speed, x, y), role(role), health(health) {}

    ~Agent() = default;

    Agent(const Agent &rhs) : SimObject(rhs), MovingObject(rhs) {
        role = rhs.role;
        health = rhs.health;
        isAlive = rhs.health;
    }


    Agent(Agent &&lhs) noexcept: SimObject(std::move(lhs.name)), MovingObject(std::move(lhs)) {
        role = lhs.role;
        health = lhs.health;
        isAlive = lhs.isAlive;
        lhs.name = "";
        lhs.role = 'A';
        lhs.health = 0;
        lhs.isAlive = false;
    }

    Agent &operator=(const Agent &rhs) {
        if (this != &rhs) {
            SimObject::operator=(rhs);
            MovingObject::operator=(rhs);
            role = rhs.role;
            health = rhs.health;
            isAlive = rhs.isAlive;
        }
        return *this;
    }

    Agent &operator=(Agent &&lhs) noexcept {
        if (this != &lhs) {
            SimObject::operator=(lhs);
            MovingObject::operator=(lhs);
            role = lhs.role;
            health = lhs.health;
            isAlive = lhs.isAlive;
            lhs.role = 'A';
            lhs.health = 0;
            isAlive = false;

        }
        return *this;
    }

    char getRole() const { return role; }

    void setRole(char newRole) { role = newRole; }

    int getHealth() const { return health; }

    void setHealth(int newHealth) { health = newHealth; }

    bool getIsAlive() const { return isAlive; }

    void setIsAlive(bool newIsAlive) { isAlive = newIsAlive; }

    void broadcastCurrentState() const override {
        std::cout << std::fixed << setprecision(2) << name << " at (" << currentX << ", " << currentY << "), ";
        if (!isAlive) {
            cout << "Dead" << endl;
        }
        else if (stopped) {
            cout << "Stopped" << endl;
        }
        else if (movement == POSITION) {
            cout << "Heading to (" << getNewX() << ", " << getNewY() << "), ";
            cout << "speed " << speed << " km/h" << endl;

        } else if (movement == COURSE){
            cout << "Heading on course " << course << " deg, speed 10.00 km/h" << endl;
        }
    }

    Agent &operator++() {
        ++health;
        return *this;
    }

    Agent &operator--() {
        --health;
        return *this;
    }
};

#endif //INC_03_AGENT_H
