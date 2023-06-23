//
// Created by Mali Abramovitch on 16/06/2023.
//

#include "Model.h"
#include "Farm.h"


#include <utility>

Farm::Farm(const std::string& name, double x, double y, int boxesInStorage, int bph) :
        Structure(name, x, y, boxesInStorage, bph) {}

void Farm::withdraw(int boxes) {
    boxesInStorage -= boxes;
}

void Farm::operator-=(int boxes) {
    withdraw(boxes);
}

void Farm::update() {
    boxesInStorage += boxesPerHour;
}

void Farm::broadcastCurrentState() const{
    //cout << "Farm ";
    Structure::broadcastCurrentState();

}

void Farm::deposit(int boxes) {
    return;
}
