//
// Created by iwant on 7/1/2025.
//

#include "eng.h"

void eng::processEvents() {
}

void eng::enqueuePersistentEvent(Event &theEvent) {
}

void eng::enqueueEvent(const Event& theEvent) {
    for (auto iter = eventQueue.begin(); iter != eventQueue.end(); iter++) {
        if (iter->eventOriginCharacter.getID() == theEvent.eventOriginCharacter.getID()) {

        }
    }
}
