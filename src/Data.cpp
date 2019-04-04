#include "Data.h"

Data::Data(const Vector2u &windowSize, const Vector2u &fieldSize, EVENT gameEvent) :
    fieldSize(fieldSize), field(fieldSize.x, fieldSize.y), gameEvent(gameEvent) {
    windowWasResized(windowSize);
}

const Vector2i &Data::getAnchor() const {
    return anchor;
}

const Vector2u &Data::getCellSize() const {
    return cellSize;
}

const Vector2u &Data::getFieldSize() const {
    return fieldSize;
}

EVENT Data::getGameEvent() const {
    return gameEvent;
}

void Data::setGameEvent(EVENT gameEvent) {
    Data::gameEvent = gameEvent;
}

Field &Data::getField() {
    return field;
}

void Data::windowWasResized(Vector2u windowSize) {
    unsigned  borderRadius = std::max(windowSize.x, windowSize.y)/20,
              maxOfTableSize = std::max(fieldSize.x, fieldSize.y + 1), // + 1 for win-lines colors
              maxCellSize = std::min(windowSize.x-2*borderRadius, windowSize.y-2*borderRadius)/maxOfTableSize;
    cellSize = {maxCellSize, maxCellSize};
    anchor = Vector2i(windowSize.x - maxCellSize * fieldSize.x, windowSize.y - maxCellSize * (fieldSize.y + 1)) / 2;
    anchor.y += maxCellSize; //For win-lines color circles
}
