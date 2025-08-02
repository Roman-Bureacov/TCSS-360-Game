//
// Created by riley on 7/23/25.
//
// This file just contains any utilities that we,
// might need over the course of the project.


#ifndef UTILS_H
#define UTILS_H
namespace util {


    struct Point {
        int x = 0;
        int y = 0;

        Point() = default;
        Point(const int theXCord, const int theYCord)
            : x(theXCord), y(theYCord) {}
    };



}
#endif //UTILS_H
