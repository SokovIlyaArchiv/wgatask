#ifndef TESTSFML_INTERFACEHANDLER_H
#define TESTSFML_INTERFACEHANDLER_H

#include <SFML/Window.hpp>

#include "Data.h"

class InterfaceHandler {
public:
    InterfaceHandler(RenderWindow& window, Data& data);
    void handle();
private:
    size_t getCellNumberByCoord(Vector2i coords) const;
    RenderWindow& window;
    Data& data;
};


#endif
