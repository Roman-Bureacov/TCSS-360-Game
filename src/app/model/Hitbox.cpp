//
// Created by iwant on 8/1/2025.
//

#include "../../include/Hitbox.h"

Hitbox::Hitbox(const util::Point& theOrigin, const int theWidth, const int theHeight)
    : myOrigin(theOrigin), myWidth(theWidth), myHeight(theHeight){
}

void Hitbox::setOrigin(const util::Point& theNewOrigin) {
    myOrigin = theNewOrigin;
}

const util::Point & Hitbox::getOrigin() const {
    return myOrigin;
}

void Hitbox::setOriginX(const int newX) {
    myOrigin.x = newX;
}

void Hitbox::setOriginY(const int newY) {
    myOrigin.y = newY;
}

int Hitbox::getWidth() const {
    return myOrigin.x;
}

int Hitbox::getHeight() const {
    return myOrigin.y;
}

bool Hitbox::contains(const util::Point thePoint) const {
    return contains(thePoint.x, thePoint.y);
}

bool Hitbox::contains(const int theX, const int theY) const {
    const int endX = myOrigin.x + myWidth;
    const int endY = myOrigin.y + myHeight;
    
    return myOrigin.x <= theX && theX <= endX
            && myOrigin.y <= theY && theY <= endY;
}

bool Hitbox::intersects(Hitbox theOtherHitbox) const {
    // TODO: is this the best way to go about intersection detection?
    const util::Point otherOrigin = theOtherHitbox.getOrigin();
    const int otherEndX = otherOrigin.x + theOtherHitbox.getWidth();
    const int otherEndY = otherOrigin.y + theOtherHitbox.getWidth();
    return
        contains(otherOrigin)
        || contains(otherEndX, otherOrigin.y)
        || contains(otherOrigin.x, otherEndY)
        || contains(otherEndX, otherEndY);
}
