//
// Created by Mali Abramovitch on 08/06/2023.
//

#ifndef INC_03_STRUCTURE_H
#define INC_03_STRUCTURE_H

#include <string>
#include <utility>
#include <iostream>
#include "Model.h"

class Structure : virtual public SimObject {
protected:
    std::string name;
    double x = 0;
    double y = 0;
    int boxesInStorage;
    int boxesPerHour;

public:
    explicit Structure(const std::string&  name, double x, double y, int boxesInStorage, int boxesPerHour = 0) :
            SimObject(name), x(x), y(y), boxesInStorage(boxesInStorage), boxesPerHour(boxesPerHour) {}

    Structure(const Structure &) = delete;

    Structure(Structure &&) = delete;

    Structure &operator=(const Structure &) = delete;

    Structure &operator=(Structure &&) = delete;

    ~Structure() override = default;

    double getX() const { return x; }

    double getY() const { return y; }

    int getBoxesInStorage() const { return boxesInStorage; }

    virtual void withdraw(int boxes) = 0;

    virtual void deposit(int boxes) = 0;

    /**SimObject**/

    void broadcastCurrentState() const override {

        std::cout << name << ' ';
        std::cout << '(' << x << ", " << y << ")";
        std::cout << ", Inventory: " << boxesInStorage << std::endl;
    }
};

#endif //INC_03_STRUCTURE_H
