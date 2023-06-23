//
// Created by Mali Abramovitch on 08/06/2023.
//

#ifndef INC_03_KNIGHT_H
#define INC_03_KNIGHT_H


#include <deque>
#include "Model.h"

class Knight : virtual public Agent {
    deque<weak_ptr<Structure>>& map;
    unsigned int nextDestIndex{};
public:
    explicit Knight(const std::string& name, weak_ptr<Structure>&, deque<weak_ptr<Structure>> *map, double x = 0, double y = 0, int speed = 10, char role = 'K', int health = 20);

    Knight(const Knight &) = delete;

    Knight(Knight &&) = delete;

    Knight &operator=(const Knight &) = delete;

    Knight &operator=(Knight &&) = delete;

    ~Knight() override = default;

    void setDestination(shared_ptr<Structure>& nexDest) override;

    /**SimObject**/

    void broadcastCurrentState() const override;

    void update() override;
};
#endif //INC_03_KNIGHT_H
