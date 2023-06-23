//
// Created by Mali Abramovitch on 16/06/2023.
//

#include <string>
#include <utility>


#ifndef INC_03_SIMOBJECT_H
#define INC_03_SIMOBJECT_H

#endif //INC_03_SIMOBJECT_H

class SimObject {
protected:
    std::string name;
public:
    explicit SimObject(std::string  name) : name(std::move(name)) {}

    SimObject(const SimObject &rhs) = default;

    SimObject(SimObject &&lhs)  noexcept : name(std::move(lhs.name)) {
        lhs.name = "";
    }

    SimObject &operator=(const SimObject &rhs) {
        if (this != &rhs) {
            name = rhs.name;
        }
        return *this;
    }

    SimObject &operator=(SimObject &&lhs)  noexcept {
        if (this != &lhs) {
            name = lhs.name;
            lhs.name = "";
        }
        return *this;
    }

    ~SimObject() = default;

    const std::string &getName() const { return name; }

    virtual void update() = 0;

    virtual void broadcastCurrentState() const = 0;

};