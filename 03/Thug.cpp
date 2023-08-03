//
// Created by Mali Abramovitch on 08/06/2023.
//

#include "Model.h"


Thug::Thug(const std::string &name, float x, float y) :
        Agent(name, 30, x, y, 'T', 5) {}

Thug::Thug(const Thug &rhs) = default;

Thug::Thug(Thug &&lhs) noexcept: Agent(std::move(lhs)) {}

Thug &Thug::operator=(const Thug &rhs) {
    if (this != &rhs) {
        Agent::operator=(rhs);
    }
    return *this;
}

Thug &Thug::operator=(Thug &&lhs) noexcept {
    if (this != &lhs) {
        Agent::operator=(std::move(lhs));
    }
    return *this;
}

void Thug::attack() {
    if (peasantToAttack != nullptr) {
        if (!thereIsAKnight) {
            auto p = dynamic_pointer_cast<Peasant>(peasantToAttack);
            if (!p) { // dynamic cast check
                throw Model::InputDataException("Peasant dynamic cast problem in Thug::attack\n");
            }
            if (MovingObject::calculateDistance(getCurrentX(), getCurrentY(), p->getCurrentX(), p->getCurrentY()) > 1) {
                cout << name << "'s attack failed! " << name << " is too far from " << p->getName() << endl;
                p->wasAttacked(true);
            } else if (health <= p->getHealth()) {
                cout << name << "'s attack failed! " << name << "'s health = " << health << " < "<< p->getName() << "'s health = " << p->getHealth() << endl;
                p->wasAttacked(true);
                --health;
                movement = STOPPED;
                stopped = true;
            } else {
                cout << name << "'s attack on " << p->getName() << " succeeded!" << endl;
                p->wasAttacked(false);
                ++health;
            }

        } else { //there is a Knight
            cout << name << "'s attack failed! there is a Knight in the area" << endl;
            --health;
            movement = STOPPED;
            stopped = true;
        }
        peasantToAttack = nullptr;
        thereIsAKnight = false;
    }
    if (health < 1) {
        isAlive = false;
    }
}


void Thug::broadcastCurrentState() const {
    cout << "Thug ";
    Agent::broadcastCurrentState();
}

void Thug::update() {
    attack();
}

void Thug::setPeasantToAttack(shared_ptr<Agent> &peasant, bool KnightIsNear) {
    peasantToAttack = peasant;
    thereIsAKnight = KnightIsNear;
}
