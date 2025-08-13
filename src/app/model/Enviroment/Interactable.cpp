//
// Created by iwant on 8/9/2025.
//

#include "../../../include/Interactable.h"


Interactable::Interactable(const Hitbox& theHitbox) :
    myHitbox(theHitbox) {

}

const Hitbox &Interactable::getHitbox() const {
    return myHitbox;
}
