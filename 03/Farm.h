//
// Created by Mali Abramovitch on 16/06/2023.
//

#ifndef INC_03_FARM_H
#define INC_03_FARM_H


#include "Model.h"

class Farm : public Structure {
    int boxesPerHour;
public:
    Farm(const std::string& name, float x, float y, int boxesInStorage, int bph);

    Farm(const Farm &);

    Farm(Farm &&) noexcept ;

    Farm &operator=(const Farm &);

    Farm &operator=(Farm &&) noexcept ;

    ~Farm() = default;

    int getBoxesPerHour() const;

    int withdraw() override;

    void deposit(int boxes) override;

    /**SimObject**/
    void broadcastCurrentState() const override;

    void update() override;
};


#endif //INC_03_FARM_H
