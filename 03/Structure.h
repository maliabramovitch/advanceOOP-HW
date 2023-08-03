//
// Created by Mali Abramovitch on 08/06/2023.
//

#ifndef INC_03_STRUCTURE_H
#define INC_03_STRUCTURE_H

#include <string>
#include <utility>
#include <iostream>
#include "Model.h"

class Structure : public SimObject {
protected:
    float x = 0;
    float y = 0;
    int boxesInStorage;

public:
    explicit Structure(const std::string &name, float x, float y, int boxesInStorage, int boxesPerHour = 0) :
            SimObject(name), x(x), y(y), boxesInStorage(boxesInStorage) {}

    Structure(const Structure &rhs) : SimObject(rhs.name) {
        x = rhs.x;
        y = rhs.y;
        boxesInStorage = rhs.boxesInStorage;
    };

    Structure(Structure &&lhs) noexcept: SimObject(lhs.name) {
        x = lhs.x;
        y = lhs.y;
        boxesInStorage = lhs.boxesInStorage;
        lhs.name = "";
        lhs.x = 0;
        lhs.y = 0;
        lhs.boxesInStorage = 0;
    }

    Structure &operator=(const Structure &rhs) {
        if (this != &rhs) {
            x = rhs.x;
            y = rhs.y;
            boxesInStorage = rhs.boxesInStorage;
        }
        return *this;
    }

    Structure &operator=(Structure &&lhs) noexcept {
        if (this != &lhs) {
            name = lhs.name;
            x = lhs.x;
            y = lhs.y;
            boxesInStorage = lhs.boxesInStorage;
            lhs.name = "";
            lhs.x = 0;
            lhs.y = 0;
            lhs.boxesInStorage = 0;
        }
        return *this;
    }

    ~Structure() = default;

    float getX() const { return x; }

    float getY() const { return y; }

    int getBoxesInStorage() const { return boxesInStorage; }

    void setBoxesInStorage(int n) { boxesInStorage = n; }

    explicit operator int() const { return boxesInStorage; }

    bool operator==(const Structure &rhs) { return (name == rhs.name) & (x == rhs.x) & (y == rhs.y); }

    bool operator!=(const Structure &rhs) { return !((name == rhs.name) & (x == rhs.x) & (y == rhs.y)); }

    virtual int withdraw() = 0;

    virtual void deposit(int boxes) = 0;

    /**SimObject**/

    void broadcastCurrentState() const override {
        std::cout << name << ' ';
        std::cout << std::setprecision(2) << std::fixed << '(' << x << ", " << y << ")";
        std::cout << ", Inventory: " << boxesInStorage << std::endl;
    }

    void update() override = 0;
};

#endif //INC_03_STRUCTURE_H
