#ifndef TESTSFML_DATA_H
#define TESTSFML_DATA_H

#include "event.h"
#include "Field.h"

class Data {
public:
    Data(const Vector2u &windowSize, const Vector2u &fieldSize, EVENT gameEvent);
    const Vector2i &getAnchor() const;
    const Vector2u &getCellSize() const;
    const Vector2u &getFieldSize() const;
    EVENT getGameEvent() const;
    Field& getField();
    void setGameEvent(EVENT gameEvent);
    void windowWasResized(Vector2u windowSize);
private:
    Vector2u cellSize, fieldSize;
    Field field;
    EVENT gameEvent;
    Vector2i anchor;
};

#endif
