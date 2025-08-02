//
// Created by riley on 7/23/25.
//


#ifndef HITBOX_H
#define HITBOX_H

#include "Utils.h"


/**
 * A hitbox class that encapsulates the idea of an interactable rectangle.
 * <br>
 * Hitboxes have an origin and extend to the right and up.
 * @version July 2025
 * @author Riley Hopper
 * @author Roman Bureacov
 */
class Hitbox {
public:
    Hitbox(
        const util::Point& theOrigin,
        int theWidth,
        int theHeight
    );

    /**
     * Sets the origin of this hitbox
     * @param theNewOrigin the new origin for this hitbox
     */
    void setOrigin(const util::Point& theNewOrigin);

    /**
     * Sets the new X origin for this hitbox
     * @param newX the new X origin in pixels
     */
    void setOriginX(int newX);

    /**
     * Sets the new Y origin for this hitbox
     * @param newY the new Y origin in pixels
     */
    void setOriginY(int newY);

    /**
     * Gets the origin of this hitbox.
     * @return the origin of this hitbox in pixels
     */
    const util::Point& getOrigin() const;

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
     * Asks if this hitbox contains the coordinate
     * @param theX the X coordinate to query
     * @param theY the Y coordinate to query
     * @return if this hitbox contains the coordinate
     */
    bool contains(int theX, int theY) const;

    /**
     * Asks if this hitbox intersects another hitbox.
     * @param theOtherHitbox the other hitbox to test for intersect
     * @return if this hitbox intersects the other hitbox
     */
    bool intersects(Hitbox theOtherHitbox) const;

private:
    util::Point myOrigin;

    const int myWidth;
    const int myHeight;
};



#endif //HITBOX_H
