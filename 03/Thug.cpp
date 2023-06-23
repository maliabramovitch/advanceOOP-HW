//
// Created by Mali Abramovitch on 08/06/2023.
//

#include "Thug.h"

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

bool Thug::attack(const std::weak_ptr<Agent> &peasant) {
    if (health > peasant.lock()->getHealth()) {
        auto p = dynamic_pointer_cast<Peasant>(peasant.lock());
        p->wasAttacked();
        ++health;
        stopped = true;
        ++health;
    } else {
        setHealth(peasant.lock()->getHealth() - 1);
        --health;
    }
}

void Thug::broadcastCurrentState() const {
    cout << "Thug ";
    Agent::broadcastCurrentState();
    if (position) {
        cout << "Heading to (" << getNewX() << ", " << getNewY() << "), ";
        cout << "speed " << speed << " km/h" << endl;
    } else {
        cout << "Heading on course " << course << " deg, speed " << speed << " km/h" << endl;
    }
}

void Thug::update() {
    if (!stopped) {
        move(speed);
    }
}
