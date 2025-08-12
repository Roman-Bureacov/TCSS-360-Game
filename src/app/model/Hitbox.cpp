//
// Created by iwant on 8/1/2025.
//

#include "../../include/Hitbox.h"

#include <stdexcept>

Hitbox::Hitbox(const util::Point& theOrigin, const int theWidth, const int theHeight)
    : myOrigin(theOrigin), myWidth(theWidth), myHeight(theHeight){

    if (theWidth < 0) throw std::logic_error("width must be zero or greater");
    if (theHeight < 0) throw std::logic_error("height must be zero or greater");
}

Hitbox::Hitbox(const int theX, const int theY, const int theWidth, const int theHeight)
    : Hitbox(util::Point(theX, theY), theWidth, theHeight) {

}

Hitbox::Hitbox(const int theWidth, const int theHeight)
    : Hitbox(util::Point(0,0), theWidth, theHeight) {

}

void Hitbox::setOrigin(const util::Point& theNewOrigin) {
    myOrigin = theNewOrigin;
}

void Hitbox::setOrigin(const int theNewX, const int theNewY) {
    myOrigin.x = theNewX;
    myOrigin.y = theNewY;
}

const util::Point & Hitbox::getOrigin() const {
    return myOrigin;
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

    if (!xContained) return false;

    // check the y-coordinate
    if (yMax <= yMaxOther) {
        // is y contained?
        yContained = yMax >= theOtherHitbox.getOrigin().y;
    } else yContained = myOrigin.y <= yMaxOther;

    return yContained;
}