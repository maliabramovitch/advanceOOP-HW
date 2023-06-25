//
// Created by Mali Abramovitch on 08/06/2023.
//

#ifndef INC_03_KNIGHT_H
#define INC_03_KNIGHT_H


#include <deque>
#include <queue>
#include "Model.h"

class Knight : virtual public Agent {
private:
    shared_ptr<Structure> originDestination;
    shared_ptr<Structure> currentDestination;
    shared_ptr<Structure> nextDestination;
    deque <shared_ptr<Structure>> map; // for every Knight in the game it will be the same map
    bool moving = false;
    deque <shared_ptr<Structure>> ridingMap;
public:
    explicit Knight(const std::string &name, shared_ptr<Structure> &firstDest, deque <shared_ptr<Structure>> &map);

    Knight(const Knight &rhs);

    Knight &operator=(const Knight &rhs);

    Knight(Knight &&lhs) noexcept;

    Knight &operator=(Knight &&lhs) noexcept;

    ~Knight();

    void setDestination(shared_ptr<Structure> &nexDest);

    void setPosition(float newX, float newY);

    void setCourse(float newCourse);

    /**SimObject**/

    void broadcastCurrentState() const override;

    void update() override;

    /**MovingObject**/
    void doMove(float speed) override;

};

#endif //INC_03_KNIGHT_H
