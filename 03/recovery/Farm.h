//
// Created by Mali Abramovitch on 16/06/2023.
//

#ifndef INC_03_FARM_H
#define INC_03_FARM_H


#include "Model.h"

class Farm : virtual public Structure {

public:
    Farm(const std::string& name, double x, double y, int boxesInStorage, int bph);

    Farm(const Farm &) = delete;

    Farm(Farm &&) = delete;

    Farm &operator=(const Farm &) = delete;

    Farm &operator=(Farm &&) = delete;

    ~Farm() override = default;

    void withdraw(int boxes) override;

    void deposit(int boxes) override;

    void operator-=(int);

    /**SimObject**/

    void update() override;

    void broadcastCurrentState() const override;

};


#endif //INC_03_FARM_H
