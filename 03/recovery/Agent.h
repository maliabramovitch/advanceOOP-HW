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

class Agent : virtual public SimObject, public MovingObject {
protected:
    char role; /// P = peasant/T = Thug/K = knight
    int health;
    int state = 1;
    enum {
        DEAD, STOP, IN_MOVEMENT
    };

public:
    /**Agent**/
    explicit Agent(const std::string &name, weak_ptr<Structure> &location, double x = 0, double y = 0,
                   int speed = 10, char role = 'K', int health = 20) :
            SimObject(name), MovingObject(location, x, y, speed), role(role), health(health) {}

    ~Agent() override = default;

    Agent(const Agent &) = delete;

    Agent(Agent &&) = delete;

    Agent &operator=(const Agent &) = delete;

    Agent &operator=(Agent &&) = delete;

    int getState() const { return state; }

    char gerRole() const { return role; }

    void setState(int newState) {
        state = newState;
    }

    Agent &operator++() {
        if (health < 20) {
            ++health;
        }
    }

    Agent &operator--() {
        --health;
        if (health == 0) {
            state = DEAD;
        }
    }

    int getHealth() const { return health; };

    void setHealth(int newHealth) { health = newHealth; }

    /**SimObject**/
    void broadcastCurrentState() const override {
        std::cout << name << " at ";
        Point p(currentPosition->x, currentPosition->y), pos;
        p.print();
        std::cout << ", ";
        switch (state) {
            case DEAD:
                cout << "Dead" << endl;
                break;
            case STOP:
                cout << "Stopped" << endl;
                break;
            case IN_MOVEMENT:
                switch (movement) {
                    case DESTINATION:
                        cout << "Heading to " << destination->getName() << ", speed " << speed << "km/h" << endl;
                        break;
                    case POSITION:
                        cout << "Heading to ";
                        pos.x = newPosition->x;
                        pos.y = newPosition->y;
                        pos.print();
                        cout << ", speed " << speed << " km/h" << endl;
                        break;
                    case COURSE:
                        cout << "Heading to course" << setprecision(2) << course << "deg, " << "speed " << speed
                             << "km/h" << endl;
                        break;
                }
                break;

        }
    }

    void update() override {
        if (state != STOP) {
            startMoving();
        }

    }


};

#endif //INC_03_AGENT_H
