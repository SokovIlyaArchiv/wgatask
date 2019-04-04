#ifndef TESTSFML_EVENTHANDLER_H
#define TESTSFML_EVENTHANDLER_H

#include "Data.h"

class EventHandler {
public:
    EventHandler(Data& data);
    void handle();
    bool isTargetNearOfTile(short nOfSelectedTile, short nOfTarget) const;
private:
    void generateField();
    bool isVictory();
    Data& data;
    Field& field;
};

#endif

