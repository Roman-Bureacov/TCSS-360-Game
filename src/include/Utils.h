//
// Created by riley on 7/23/25.
//
// This file just contains any utilities that we,
// might need over the course of the project.


#ifndef UTILS_H
#define UTILS_H
namespace util {

    enum Direction {
        NORTH,
        EAST,
        SOUTH,
        WEST
    };

    struct Point {
        int x = 0;
        int y = 0;

        Point() = default;
        Point(const int theXCord, const int theYCord)
            : x(theXCord), y(theYCord) {}

        /**
         * Translates this point by the specified deltas.
         * @param theDeltaX the delta-x to translate by
         * @param theDeltaY the delta-y to translate by
         */
        void translate(const int theDeltaX, const int theDeltaY) {
            x += theDeltaX;
            y += theDeltaY;
        }

        /**
         * Convenience function to set both x and y.
         * @param theNewX the new x position
         * @param theNewY the new y position
         */
        void set(const int theNewX, const int theNewY) {
            x = theNewX, y = theNewY;
        }
    };
}
#endif //UTILS_H
