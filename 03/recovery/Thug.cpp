//
// Created by Mali Abramovitch on 08/06/2023.
//

#include "Thug.h"

Thug::Thug(const std::string &name, double x, double y, shared_ptr<Structure> dest) :
        SimObject(name), Agent(name, dest, x, y, 30, 'T', 5) {}

bool Thug::attack(const std::shared_ptr<Agent>& peasant) {
    if (health > peasant->getHealth()) {
        auto p = dynamic_pointer_cast<Peasant>(peasant);
        p->wasAttacked();
        ++health;
        state = STOP;
        ++(*this);
    } else {
        --(*peasant);
        --(*this);
    }
}

void Thug::broadcastCurrentState() const {
    cout << "Thug ";
    Agent::broadcastCurrentState();
}
