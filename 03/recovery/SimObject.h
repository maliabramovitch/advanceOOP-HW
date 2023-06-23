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
    explicit SimObject(std::string name) : name(std::move(name)) {}

    SimObject(const SimObject &) = delete;

    SimObject(SimObject &&) = delete;

    SimObject &operator=(const SimObject &) = delete;

    SimObject &operator=(SimObject &&) = delete;

    virtual ~SimObject() = default;

    const std::string &getName() const { return name; }

    virtual void update() = 0;

    virtual void broadcastCurrentState() const = 0;

};