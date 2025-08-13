//
// Created by iwant on 8/9/2025.
//

#ifndef DOOR_H
#define DOOR_H
#include "../../../include/Bitz.h"
#include "../../../include/Interactable.h"

class Door : public Interactable {
private:
    const int myNextRoomID;
public:
    /**
     * Constructs a door interactable, where upon interaction will cause
     * the engine to load the next room.
     * @param theHitbox the hitbox for this door
     * @param theNextRoomID the ID of the room this door leads into
     */
    Door(const Hitbox& theHitbox, const int theNextRoomID)
    : Interactable(theHitbox), myNextRoomID(theNextRoomID) { }

    void interact() override {
        Bitz::loadDungeonRoom(myNextRoomID);
    }
};

#endif //DOOR_H
