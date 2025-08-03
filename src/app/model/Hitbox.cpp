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
    return myWidth;
}

int Hitbox::getHeight() const {
    return myHeight;
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

bool Hitbox::intersects(const Hitbox& theOtherHitbox) const {
    // see: https://dyn4j.org/2010/01/sat/
    const int xMax = myOrigin.x + myWidth;
    const int xMaxOther = theOtherHitbox.getOrigin().x + theOtherHitbox.getWidth();
    const int yMax = myOrigin.y + myHeight;
    const int yMaxOther = theOtherHitbox.getOrigin().y + theOtherHitbox.getHeight();

    bool xContained;
    bool yContained;

    // check the x-coordinate first
    if (xMax <= xMaxOther) {
        // is x contained?
        xContained = xMax >= theOtherHitbox.getOrigin().x;
    } else xContained = myOrigin.x <= xMaxOther;

    // check the y-coordinate
    if (yMax <= yMaxOther) {
        // is y contained?
        yContained = yMax >= theOtherHitbox.getOrigin().y;
    } else yContained = myOrigin.y <= yMaxOther;

    return xContained && yContained;
}
