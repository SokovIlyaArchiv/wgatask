#ifndef TESTSFML_GAME_H
#define TESTSFML_GAME_H

#include "InterfaceDrawer.h"
#include "InterfaceHandler.h"
#include "EventHandler.h"

class Game {
public:
    Game(Vector2u windowSize);
    void exec();
private:
    RenderWindow window;
    Data data;
    EventHandler eventHandler;
    InterfaceHandler interfaceHandler;
    InterfaceDrawer interfaceDrawer;
};


#endif