//
// Created by iwant on 8/9/2025.
//

#ifndef INTERACTIBLE_H
#define INTERACTIBLE_H

#include "Hitbox.h"

class Interactable {
private:
    Hitbox myHitbox;
public:
    virtual ~Interactable() = default;

    Interactable(const Hitbox& theHitbox);
    const Hitbox& getHitbox() const;
    virtual void interact() = 0;
};



#endif //INTERACTIBLE_H
