//
// Created by Mali Abramovitch on 16/06/2023.
//

#ifndef INC_03_CASTLE_H
#define INC_03_CASTLE_H

#include "Structure.h"

class Castle : public Structure {
public:
    Castle(const std::string& name, float x, float y, int boxesInStorage);

    ~Castle() = default;

    Castle(const Castle &rhs) = default;

    Castle(Castle &&lhs) = default;

    Castle &operator=(const Castle &rhs) = default;

    Castle &operator=(Castle &&lhs) = default;

    void deposit(int boxes) override;

    int withdraw(int boxes) override;

    void operator+=(int boxes);

    /**SimObject**/

    void update() override;

    void broadcastCurrentState() const override;
};


#endif //INC_03_CASTLE_H
