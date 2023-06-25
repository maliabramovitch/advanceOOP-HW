//
// Created by Mali Abramovitch on 16/06/2023.
//

#include "Model.h"


#include <utility>

Farm::Farm(const std::string &name, float x, float y, int boxesInStorage, int bph) :
        Structure(name, x, y, boxesInStorage), boxesPerHour(bph) {}

Farm::Farm(const Farm &rhs) = default;

Farm::Farm(Farm &&lhs) noexcept = default;

Farm &Farm::operator=(const Farm &rhs) = default;

Farm &Farm::operator=(Farm &&lhs) noexcept = default;

int Farm::getBoxesPerHour() const { return boxesPerHour; }

int Farm::withdraw() {
    if (boxesInStorage > boxesPerHour) {
        boxesInStorage -= boxesPerHour;
        return boxesPerHour;
    }
    int boxes = boxesInStorage;
    boxesInStorage = 0;
    return boxes;
}

void Farm::update() {
    boxesInStorage += boxesPerHour;
}

void Farm::broadcastCurrentState() const {
    cout << "Farm ";
    Structure::broadcastCurrentState();
}

void Farm::deposit(int boxes) {}
