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
    class Comparator {
        const weak_ptr<Structure>& myDest;
    public:
        explicit Comparator(const weak_ptr<Structure> &myDest) : myDest(myDest){};
        bool operator()( const weak_ptr<Structure> &dest1, const weak_ptr<Structure> &dest2);
    };
    bool destination = false;
    weak_ptr<Structure> originDestination;
    weak_ptr<Structure> currentDestination;
    weak_ptr<Structure> nextDestination;
    const deque<weak_ptr<Structure>> &map; // for every Knight in the game it will be the same map
    bool moving = false;

    /**
     * priority queue for choosing the riding course;
     * @param currentDest
     */
    deque<weak_ptr<Structure>> ridingMap;

    /**
     * creating minimum heap
     * @param myDest
     */
    void sortRidingMap(const weak_ptr<Structure> &myDest);

public:
    explicit Knight(const std::string &name, weak_ptr<Structure> &firstDest, deque<weak_ptr<Structure>> &map);

    Knight(const Knight &rhs);

    Knight &operator=(const Knight &rhs);

    Knight(Knight &&lhs) noexcept;

    Knight &operator=(Knight &&lhs) noexcept;

    ~Knight() ;

    void setDestination(weak_ptr<Structure> &nexDest);

    void setPosition(float newX, float newY);

    void setCourse(float newCourse);

    /**SimObject**/

    void broadcastCurrentState() const override;

    void update() override;

    /**MovingObject**/
    void move(float speed) override;

};

#endif //INC_03_KNIGHT_H
