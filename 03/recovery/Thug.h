//
// Created by Mali Abramovitch on 08/06/2023.
//

#ifndef INC_03_THUG_H
#define INC_03_THUG_H


#include <memory>
#include "Model.h"

class Thug : virtual public Agent {
public:
    Thug(const std::string& name, double x, double y, shared_ptr<Structure> dest = nullptr);

    bool attack(const std::shared_ptr<Agent>& peasant);

    /**SimObject**/

    void broadcastCurrentState() const override;
};


#endif //INC_03_THUG_H
