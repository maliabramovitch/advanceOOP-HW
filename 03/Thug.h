//
// Created by Mali Abramovitch on 08/06/2023.
//

#ifndef INC_03_THUG_H
#define INC_03_THUG_H


#include <memory>
#include "Model.h"

class Thug : virtual public Agent {
    shared_ptr<Agent> peasantToAttack = nullptr;
public:
    Thug(const std::string &name, float x, float y);

    Thug(const Thug &rhs);

    Thug(Thug &&lhs) noexcept;

    Thug &operator=(const Thug &rhs);

    Thug &operator=(Thug &&lhs) noexcept;

    bool attack();

    void srtPeasantToAttack(shared_ptr<Agent>& peasant);
    /**SimObject**/

    void broadcastCurrentState() const override;

    void update() override;
};


#endif //INC_03_THUG_H