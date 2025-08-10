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
    /**
     * Constructs a new hitbox at the point specified.
     * @param theOrigin where the hitbox is constructed at
     * @param theWidth the width of this hitbox
     * @param theHeight the height of this hitbox
     */
    Hitbox(
        const util::Point& theOrigin,
        int theWidth,
        int theHeight
    );

    /**
     * Constructs a new hitbox at the coordinates specified.
     * @param theX the x position of this hitbox
     * @param theY the y position of this hitbox
     * @param theWidth the width of this hitbox
     * @param theHeight the height of this hitbox
     */
    Hitbox(
        int theX,
        int theY,
        int theWidth,
        int theHeight
    );

    /**
     * Constructs a new hitbox at (0,0).
     * @param theWidth the width of this hitbox
     * @param theHeight the height of this hitbox
     */
    Hitbox(
        int theWidth,
        int theHeight
    );

    /**
     * Sets the origin of this hitbox
     * @param theNewOrigin the new origin for this hitbox
     */
    void setOrigin(const util::Point& theNewOrigin);

    /**
     * Set the origin of this hitbox.
     * @param theNewX the new x position of the origin
     * @param theNewY the new y position of the origin
     */
    void setOrigin(int theNewX, int theNewY);

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
    bool intersects(const Hitbox& theOtherHitbox) const;

    /**
     * Projects the other hitbox on this hitbox in the direction. The
     * projected hitbox will be centered in the desired direction.
     * @param theOtherHitbox the hitbox to project on this hitbox
     * @param theDirection the direction to project.
     */
    void project(Hitbox& theOtherHitbox, const util::Direction theDirection) const;

private:
    util::Point myOrigin;

    int myWidth;
    int myHeight;
};



#endif //HITBOX_H
