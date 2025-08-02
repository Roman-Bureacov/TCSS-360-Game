//
// Created by riley on 7/23/25.
//


#ifndef HITBOX_H
#define HITBOX_H

#include "Utils.h"


/**
 * A hitbox class that encapsulates the idea of an interactable rectangle.
 * @version July 2025
 * @author Riley Hopper
 * @author Roman Bureacov
 */
class Hitbox {
public:
    Hitbox(
        util::Point middle,
        int theWidth,
        int theHeight
    );

    void setMiddle(util::Point theMiddle);

    const util::Point& getMiddle() const;

    /**
     * Gets the width of this hitbox.
     * @return the width of this hitbox in pixels
     */
    int getWidth() const;

    /**
     * Gets the height of this hitbox.
     * @return the height of this hitbox in pixels
     */
    int getHeight() const;

    /**
     * Asks if this hitbox contains the point.
     * @param thePoint the point to test for containment
     * @return if this hitbox contains the point
     */
    bool contains(util::Point thePoint) const;

    /**
     * Asks if this hitbox intersects another hitbox.
     * @param theOtherHitbox the other hitbox to test for intersect
     * @return if this hitbox intersects the other hitbox
     */
    bool intersects(Hitbox theOtherHitbox) const;


private:
    util::Point myMiddle;

    const int myWidth;
    const int myHeight;




};



#endif //HITBOX_H
