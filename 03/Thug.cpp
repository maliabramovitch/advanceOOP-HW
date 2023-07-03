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

bool Thug::attack() {
    if (peasantToAttack != nullptr) {
        auto p = dynamic_pointer_cast<Peasant>(peasantToAttack);
        if (!p) {
            throw Model::InputDataException("Peasant dynamic cast problem in Thug::attack\n");
        }
        if (health < p->getHealth() || thisIsAKnight) {
            p->wasAttacked(true);
            cout << name << "'s attack succeeded!" << endl;
        } else {
            p->wasAttacked(false);
            cout << name << "'s attack failed!" << endl;
        }
        peasantToAttack = nullptr;
        thisIsAKnight = false;
    }
}

void Thug::broadcastCurrentState() const {
    cout << "Thug ";
    Agent::broadcastCurrentState();
}

void Thug::update() {
    attack();
}

void Thug::setPeasantToAttack(shared_ptr<Agent>& peasant, bool KnightIsClosed) {
    peasantToAttack = peasant;
    thisIsAKnight = true;
}
