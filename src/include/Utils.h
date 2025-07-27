//
// Created by riley on 7/23/25.
//
// This file just contains any utilities that we,
// might need over the course of the project.


#ifndef UTILS_H
#define UTILS_H
namespace util {


    struct Point {
        float x = 0.0f;
        float y = 0.0f;

        Point() = default;
        Point(float const theXCord, float const theYCord)
            : x(theXCord), y(theYCord) {}
    };



}
#endif //UTILS_H
