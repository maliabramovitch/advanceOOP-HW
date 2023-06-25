//
// Created by Mali Abramovitch on 16/06/2023.
//
#include "Model.h"
//#include "Castle.h"


#include <utility>

Castle::Castle(const std::string& name, float x, float y, int boxesInStorage) :
        Structure(name, x, y, boxesInStorage) {}


void Castle::deposit(int boxes) {
    boxesInStorage += boxes;
}

void Castle::operator+=(int boxes) {
    deposit(boxes);
}

void Castle::update() {}

void Castle::broadcastCurrentState() const {
    cout << "Castle ";
    Structure::broadcastCurrentState();
}

int Castle::withdraw() {return 0;}
