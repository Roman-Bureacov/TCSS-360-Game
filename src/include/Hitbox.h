//
// Created by riley on 7/23/25.
//


#ifndef HITBOX_H
#define HITBOX_H

#include "Utils.h"



class Hitbox {
public:
    Hitbox(const util::Point middle,
        const float theWidth,
        const float theHeight);

    void setMiddle(util::Point theMiddle);

    util::Point getMiddle() const;
    float getWidth() const;
    float getHeight() const;

    bool isContained(util::Point thePoint) const;


private:
    util::Point myMiddle;

    const float myWidth;
    const float myHeight;




};



#endif //HITBOX_H
